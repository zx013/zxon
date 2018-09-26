# -*- coding: utf-8 -*-
"""
Created on Wed Sep 26 13:24:31 2018

@author: zx013
"""
import numpy as np
import matplotlib.pyplot as plt


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

    def __init__(self, spike_type='RS', num=1, *args, **kwargs):
        self.num = num
        self.spike_type = spike_type
        self.a, self.b, self.c, self.d = self.params[spike_type]

        self.v = np.ones(num) * -65
        self.u = np.ones(num) * self.b * self.v
        self.I = np.zeros(num)
        self.g = np.zeros(num)
        self.I_ext = np.zeros(num)

        self.lastspike = np.zeros(num)
        self.spikes = []
        for i in range(num):
            self.spikes.append([])

        self.t = 0

        self.record_t = np.zeros(0)
        self.record_v = np.zeros((num, 0))
        self.record()

    def next(self):
        self.t += 1

        step = 2
        for i in range(step):
            self.v += (0.04 * self.v ** 2 + 5 * self.v + 140 - self.u + np.clip(self.I + self.I_ext, -20, 40)) / step
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
    def __init__(self, izh_pre, izh_post, num=100, rate=0, stdp_type='normal', connect_type='all', condition='1'):
        self.izh_pre = izh_pre
        self.izh_post = izh_post #突触连接到的神经元
        self.num = num
        self.t = 0

        self.link = np.ones((self.izh_pre.num, self.izh_post.num)) #连接矩阵
        self.i = np.zeros(0, dtype=np.int)
        self.j = np.zeros(0, dtype=np.int)
        self.size = 0
        for i in range(self.izh_pre.num):
            for j in range(self.izh_post.num):
                if not eval(condition):
                    self.link[i][j] = 0
                if not self.link[i][j]:
                    continue
                self.i = np.append(self.i, i)
                self.j = np.append(self.j, j)
                self.size += 1

        self.stdp_type = stdp_type
        if stdp_type == 'depress': #LTS -> CH
            self.w = -1 - np.random.rand(self.size, 100)
        else:
            self.w = np.random.rand(self.size, 100)
            if stdp_type == 'part': #CH -> LTS
                for i in range(num):
                    if (i % 2 == 0) or (i % 3 == 0) or (i % 7 == 0):
                        self.w[:, i] = 0

        self.rate = rate
        self.trace = np.zeros((self.size, num))
        self.delay = np.tile(np.arange(num), self.size).reshape(self.size, num)

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

        if self.stdp_type == 'normal':
            self.trace *= 0.8 #遗忘速率
            self.trace += (1.21 * np.exp(-(delta + 12.7) ** 2 / 13.61 ** 2) - 0.21) * spike
            self.w = np.clip(self.w + self.rate * self.trace * spike, 0, 1)


class Network:
    def __init__(self):
        self.network = []

    def add(self, izh):
        if isinstance(izh, tuple) or isinstance(izh, list):
            self.network += izh
        else:
            self.network.append(izh)

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


class Robot:
    def __init__(self, num, network, index, rate):
        self.num = num #神经元数量
        self.network = network
        self.location = -300 #线索的初始坐标
        self.maximun = 1000 #机械臂最大偏移，右边为正
        self.minimun = -1000
        self.trace = np.zeros(1) #第一个为数量
        self.trace = np.append(self.trace, self.location)
        self.index = index
        self.rate = rate


    @property
    def save_dir(self):
        return 'save-{}'.format(self.index)

    #向左或向右移动若干距离，右移时为1，左移时为-1
    def move(self, side=1, length=100):
        before = self.location
        self.location = np.clip(self.location + side * length, self.minimun, self.maximun)
        after = self.location
        self.trace[0] += 1
        self.trace = np.append(self.trace, self.location)
        return before * after <= 0 #穿过或者到达了线索

    def sense(self):
        self.input.I_ext *= 0
        step = (self.maximun - self.minimun) / self.num
        index = np.clip(int((self.location - self.minimun) / step), 0, self.num - 1)
        self.input.I_ext[index] = 10

    def run(self, during=1000, learning_rate=0):
        for stdp in self.stdp_list:
            stdp.rate = learning_rate

        left_spikes = self.left.num_spikes
        right_spikes = self.right.num_spikes
        self.network.run(during)

        left_spikes = self.left.num_spikes - left_spikes
        right_spikes = self.right.num_spikes - right_spikes
        print(list(self.input.I_ext), left_spikes, right_spikes)
        return left_spikes, right_spikes


if __name__ == '__main__':
    network = Network()
    num = 2
    Input_RS = Izhikevich('RS', num)
    CH_L = Izhikevich('CH', num)
    CH_R = Izhikevich('CH', num)
    LTS_L = Izhikevich('LTS', num)
    LTS_R = Izhikevich('LTS', num)
    Output_RS_L = Izhikevich('RS')
    Output_RS_R = Izhikevich('RS')
    network.add([Input_RS, CH_L, CH_R, LTS_L, LTS_R, Output_RS_L, Output_RS_R])

    IR_CL = STDP(Input_RS, CH_L, condition='i==j')
    IR_CR = STDP(Input_RS, CH_R, condition='i==j')
    CL_LR = STDP(CH_L, LTS_R, stdp_type='part')
    CR_LL = STDP(CH_R, LTS_L, stdp_type='part')
    CL_LL = STDP(CH_L, LTS_L, stdp_type='part', condition='i!=j')
    CR_LR = STDP(CH_R, LTS_R, stdp_type='part', condition='i!=j')
    LL_CL = STDP(LTS_L, CH_L, stdp_type='depress', condition='i==j')
    LR_CR = STDP(LTS_R, CH_R, stdp_type='depress', condition='i==j')
    CL_OL = STDP(CH_L, Output_RS_L)
    CR_OR = STDP(CH_R, Output_RS_R)
    network.add([IR_CL, IR_CR, CL_LR, CR_LL, CL_LL, CR_LR, LL_CL, LR_CR, CL_OL, CR_OR])

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


