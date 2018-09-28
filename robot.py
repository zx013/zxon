# -*- coding: utf-8 -*-
"""
Created on Wed Sep 26 13:24:31 2018

@author: zx013
"""
import os
import numpy as np
import matplotlib.pyplot as plt
from numba.cuda import autojit


def psp(t):
    if t < 0:
        return 0
    return t / 5 * np.exp(1 - t / 5)


class Izhikevich:
    params = {
        'RS': (0.02,   0.2,    -65,    8), #Regular Spiking
        'CH': (0.02,    0.2,    -50,    2), #Chattering
        'LTS': (0.02,    0.25,   -65,    2) #Low-Threshod Spiking
    }

    def __init__(self, spike_type='RS', num=1, noise=False, *args, **kwargs):
        self.num = num
        self.noise = noise
        self.spike_type = spike_type
        self.a, self.b, self.c, self.d = self.params[spike_type]

        self.reset()

    def reset(self):
        self.v = np.ones(self.num) * -65
        self.u = np.ones(self.num) * self.b * self.v
        self.I = np.zeros(self.num) #内部电流
        self.g = np.zeros(self.num)
        self.I_ext = np.zeros(self.num) #外部电流
        self.I_noise = np.zeros(self.num) #噪音

        self.lastspike = np.zeros(self.num)
        self.spikes = []
        for i in range(self.num):
            self.spikes.append([])
        self.spikes_num = np.zeros(self.num, dtype=np.int)

        self.t = 0

        self.record_t = np.zeros(0)
        self.record_v = np.zeros((self.num, 0))
        self.record()

    def next(self):
        self.t += 1
        if not self.t % 100 and self.noise:
            self.I_noise = 0.5 * np.random.rand(self.num)

        step = 2
        for i in range(step):
            I = np.clip(self.I + self.I_ext + self.I_noise, -20, 40)
            self.v += (0.04 * self.v ** 2 + 5 * self.v + 140 - self.u + I) / step
            self.u += self.a * (self.b * self.v - self.u) / step
            self.I += (self.g - self.I) / 5 / step #把psp转换成微分方程形式
            self.g += - self.g / 5 / step

        #spike = self.v > 30
        for num in range(self.num):
            if self.v[num] > 30:
                self.v[num] = self.c
                self.u[num] += self.d
                self.lastspike[num] = self.t
                self.spikes[num].append(self.t)
                self.spikes_num[num] += 1
        self.record()

    def record(self):
        self.record_t = np.append(self.record_t, self.t)
        self.record_v = np.append(self.record_v, self.v.reshape(self.num, 1), axis=1)


    def plot(self, sub):
        plt.subplot(sub)
        x = np.zeros(0)
        y = np.zeros(0)
        for num in range(self.num):
            x = np.append(x, self.spikes[num])
            y = np.append(y, np.ones(len(self.spikes[num])) * num)
        plt.plot(x, y, 'o', markersize=3)
        #plt.legend()
        plt.xlim((- 0.05 * self.t, 1.05 * self.t))
        plt.ylim((- 0.2, self.num - 0.8))
        #plt.xticks()
        plt.yticks(np.arange(self.num))
        plt.xlabel('t (ms)')
        plt.ylabel('index')



class STDP:
    def __init__(self, izh_pre, izh_post, num=100, rate=0, learning=False, part=False, depress=False, condition='1', w=None, r=0):
        self.izh_pre = izh_pre
        self.izh_post = izh_post #突触连接到的神经元
        self.num = num #突触连接数量，默认100
        self.rate = rate #训练速度，默认0，后续通过多巴胺浓度调节
        self.learning = learning #是否需要进行训练
        self.part = part #是否只取一部分生效
        self.depress = depress #是否是抑制神经元
        self.condition = condition #神经元筛选条件
        self.w = w
        self.r = r

        self.init()
        self.reset()

    def reset(self):
        self.t = 0
        self.trace = np.zeros((self.size, self.num))

    def init(self):
        self.link = np.ones((self.izh_pre.num, self.izh_post.num)) #连接矩阵
        self.i = np.zeros(0, dtype=np.int)
        self.j = np.zeros(0, dtype=np.int)
        self.size = 0
        for i in range(self.izh_pre.num):
            for j in range(self.izh_post.num):
                if not eval(self.condition):
                    self.link[i][j] = 0
                if not self.link[i][j]:
                    continue
                self.i = np.append(self.i, i)
                self.j = np.append(self.j, j)
                self.size += 1

        if self.w is not None:
            self.w += self.r * np.repeat([np.random.rand(self.num)], self.size, axis=0) - self.r * np.repeat([np.random.rand(self.num)], self.size, axis=0)

            if self.depress:
                self.w = np.clip(self.w, -2, -1)
            else:
                self.w = np.clip(self.w, 0, 1)
        else:
            if self.depress: #LTS -> CH
                self.w = -1 - np.repeat([np.random.rand(self.num)], self.size, axis=0)
            else:
                self.w = np.repeat([np.random.rand(self.num)], self.size, axis=0)

        if self.part: #CH -> LTS
            for i in range(self.num):
                if (i % 2 == 0) or (i % 3 == 0) or (i % 7 == 0):
                    self.w[:, i] = 0

        self.delay = np.repeat([np.arange(self.num)], self.size, axis=0)


    def next(self):
        self.t += 1

        spike = np.zeros((self.size, self.num))
        delta = np.zeros((self.size, self.num))
        for index in range(self.size):
            i = self.i[index]
            j = self.j[index]
            if not self.link[i][j]:
                continue
            for t in self.izh_pre.spikes[i][::-1]: #时间t经过延时后恰好是当前时间
                if self.t - t > 130:
                    break
                spike[index] += self.t == t + self.delay[index]

            self.izh_post.g[j] += sum(self.w[index] * spike[index])
            delta[index] = self.izh_post.lastspike[j] - self.izh_pre.lastspike[i]

        if self.learning:
            self.trace *= 0.8 #遗忘速率
            self.trace += (1.21 * np.exp(-(delta + 12.7) ** 2 / 13.61 ** 2) - 0.21) * spike
            self.w = np.clip(self.w + self.rate * self.trace * spike, 0, 1)


class Network:
    def __init__(self):
        self.network = []
        self.input = []
        self.output = []
        self.stdp = []

    def add(self, izh, izh_type='middle'):
        if not isinstance(izh, tuple) and not isinstance(izh, list):
            izh = [izh]
        if izh_type == 'input':
            self.input += izh
        elif izh_type == 'output':
            self.output += izh
        for stdp in izh:
            if not isinstance(stdp, STDP):
                continue
            if stdp.learning:
                self.stdp.append(stdp)
        self.network += izh

    def next(self):
        for izh in self.network:
            if not isinstance(izh, Izhikevich):
                continue
            izh.next()
        for stdp in self.network:
            if not isinstance(stdp, STDP):
                continue
            stdp.next()

    def run(self, dt):
        for i in range(dt):
            self.next()

    def reset(self):
        for izh in self.network:
            if isinstance(izh, Izhikevich):
                izh.reset()
            if isinstance(izh, STDP):
                izh.reset()


class Robot:
    def __init__(self, num, network, index, rate):
        self.num = num #神经元数量
        self.network = network #决策网络
        self.rate = rate #训练速率
        self.index = index #存储序号

        self.location = -300 #线索的初始坐标
        self.cue = 0
        self.maximun = 1000 #机械臂最大偏移，右边为正
        self.minimun = -1000
        self.trace = np.zeros(1) #第一个为数量
        self.trace = np.append(self.trace, self.location)


    #向左或向右移动若干距离，右移时为1，左移时为-1
    def move(self, side=1, length=100):
        before = self.location - self.cue
        self.location = np.clip(self.location + side * length, self.minimun, self.maximun)
        after = self.location - self.cue
        self.trace[0] += 1
        self.trace = np.append(self.trace, self.location)
        return before and before * after <= 0 #穿过或者到达了线索

    def sense(self):
        input = self.network.input[0]
        input.I_ext *= 0
        step = (self.maximun - self.minimun) / self.num
        index = np.clip(int((self.location - self.minimun) / step), 0, self.num - 1)
        input.I_ext[index] = 10

    def run(self, during=1000, rate=0):
        for stdp in self.network.stdp:
            stdp.rate = rate

        left, right = self.network.output
        left_spikes = left.spikes_num[0]
        right_spikes = right.spikes_num[0]
        self.network.run(during)

        left_spikes = left.spikes_num[0] - left_spikes
        right_spikes = right.spikes_num[0] - right_spikes
        print('run {}ms by rate {}, input {}, output {} {}'.format(during, rate, self.network.input[0].I_ext, left_spikes, right_spikes))
        return left_spikes, right_spikes

    #机械臂进行移动
    #判断线索激活的神经元
    #进行6s的决策,确保神经元产生决策
    #判断是否给予奖励或者惩罚（修改训练速率）
    #进行2s的训练
    #机械臂移动
    def next(self):
        self.sense()
        print('make decision')
        for i in range(10):
            left_spikes, right_spikes = self.run(1000)
            if left_spikes > 0 and right_spikes > 0 or left_spikes == 0 and right_spikes == 0:
                continue
            break
        else:
            print('can not make decision')
            self.network.reset()
            return

        print('start learn')
        side = -1 if left_spikes > right_spikes else 1
        length = (left_spikes + right_spikes) * 4
        rate = self.rate if self.move(side, length) else 0

        self.run(2000, rate)
        self.save()

        print('reset circuit ')
        self.network.reset() #重置神经元状态

    def plot(self, index=0, test=False, rand=0.5):
        if test:
            location = -300
            x = []
            y = []
            for i in range(1000):
                side = -1 if np.random.random() < rand else 1
                location = np.clip(location + side * 100, self.minimun, self.maximun)
                x.append(i)
                y.append(location)
        else:
            trace = np.load('save-{}/trace.npy'.format(index))
            x = np.arange(trace[0])
            y = trace[2:]
        n_old = y[1]
        s = [0, 0]
        index = 0
        for n in y:
            if n_old != n:
                index = 0 if n_old > n else 1
            s[index] += 1
            n_old = n
        print(s)

        plt.figure(figsize=(12, 6))
        plt.plot(x, y)
        plt.xlabel('Time')
        plt.ylabel('Position')

    @property
    def save_dir(self):
        return 'save-{}'.format(self.index)

    def save(self):
        if not os.path.exists(self.save_dir):
            os.mkdir(self.save_dir)
        stdp_list = [stdp for stdp in self.network.network if isinstance(stdp, STDP)]
        for num, stdp in enumerate(stdp_list):
            np.save('{}/stdp-{}.npy'.format(self.save_dir, num), stdp.w)
        np.save('{}/trace.npy'.format(self.save_dir), self.trace)

    def load(self):
        stdp_list = [stdp for stdp in self.network.network if isinstance(stdp, STDP)]
        for num, stdp in enumerate(stdp_list):
            stdp.w = np.load('{}/stdp-{}.npy'.format(self.save_dir, num))
        self.trace = np.load('{}/trace.npy'.format(self.save_dir))
        self.location = self.trace[-1]


'''
实现幅度控制的几种方案
感知距离信息，根据距离信息设置抑制效果
感知移动幅度，经过奖励后降低移动幅度
记忆之前的若干次移动，达到奖励后对之前若干次的移动都进行奖励训练（移动后之前的输入电流不会立即消失，而是逐步的降低，保证有脉冲发放，但发放频率降低，这种方案似乎可以实现同时训练多个连接突触的效果，但是之前的反向移动同样会被作为正向移动而训练）
'''
if __name__ == '__main__':
    index = 8
    rate = 0.0005
    input_numer = 2
    decision_number = 1

    network = Network()
    Input_RS = Izhikevich('RS', input_numer)
    CH_L = Izhikevich('CH', decision_number, noise=True)
    CH_R = Izhikevich('CH', decision_number, noise=True)
    LTS_L = Izhikevich('LTS', decision_number)
    LTS_R = Izhikevich('LTS', decision_number)
    Output_RS_L = Izhikevich('RS')
    Output_RS_R = Izhikevich('RS')
    network.add([Input_RS], 'input')
    network.add([CH_L, CH_R, LTS_L, LTS_R])
    network.add([Output_RS_L, Output_RS_R], 'output')

    #如果两侧权值都是全部随机，容易陷入单向的移动
    IR_CL = STDP(Input_RS, CH_L, learning=True)
    IR_CR = STDP(Input_RS, CH_R, learning=True, w=IR_CL.w)
    CL_LR = STDP(CH_L, LTS_R, part=True)
    CR_LL = STDP(CH_R, LTS_L, part=True, w=CL_LR.w)
    CL_LL = STDP(CH_L, LTS_L, part=True, condition='i!=j')
    CR_LR = STDP(CH_R, LTS_R, part=True, condition='i!=j', w=CL_LL.w)
    LL_CL = STDP(LTS_L, CH_L, depress=True, condition='i==j')
    LR_CR = STDP(LTS_R, CH_R, depress=True, condition='i==j', w=LL_CL.w)
    CL_OL = STDP(CH_L, Output_RS_L, w=1)
    CR_OR = STDP(CH_R, Output_RS_R, w=1)
    network.add([IR_CL, IR_CR, CL_LR, CR_LL, CL_LL, CR_LR, LL_CL, LR_CR, CL_OL, CR_OR])

    robot = Robot(input_numer, network, index=index, rate=rate)
    if os.path.exists('save-{}/stdp-0.npy'.format(index)):
        robot.load()
    robot.save()

    print(robot.trace[0], robot.location)
    while robot.trace[0] < 500:
        robot.next()
        print(robot.trace[0], robot.location)

    '''
    Input_RS.I_ext[0] = 10
    network.run(2000)

    plt.figure(figsize=(12, 2 * 7))

    Input_RS.plot(711)
    CH_L.plot(712)
    CH_R.plot(713)
    LTS_L.plot(714)
    LTS_R.plot(715)
    Output_RS_L.plot(716)
    Output_RS_R.plot(717)
    '''
