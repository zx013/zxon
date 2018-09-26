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
            delta[index] = self.izh_post.lastspike[i] - self.izh_pre.lastspike[j]

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
    def __init__(self, num, index, rate):
        self.num = num #神经元数量
        self.location = -300 #线索的初始坐标
        self.maximun = 1000 #机械臂最大偏移，右边为正
        self.minimun = -1000
        self.trace = np.zeros(0)
        self.trace = np.append(self.trace, 0)
        self.trace = np.append(self.trace, self.location)
        self.index = index
        self.rate = rate


    @property
    def save_dir(self):
        return 'save-{}'.format(self.index)

    #向左或向右移动若干距离，右移时为1，左移时为-1
    def move(self, side=1, length=100):
        before = self.location
        self.location += side * length
        if self.location > self.maximun:
            self.location = self.maximun
        if self.location < self.minimun:
            self.location = self.minimun
        after = self.location
        self.trace[0] += 1
        self.trace = np.append(self.trace, self.location)
        if before * after <= 0:
            return True
        else:
            return False


if __name__ == '__main__':
    network = Network()
    num = 2
    RS = Izhikevich('RS', num)
    CH_L = Izhikevich('CH', num)
    CH_R = Izhikevich('CH', num)
    LTS_L = Izhikevich('LTS', num)
    LTS_R = Izhikevich('LTS', num)
    network.add([RS, CH_L, CH_R, LTS_L, LTS_R])

    STDP_R_CL = STDP(RS, CH_L, condition='i==j')
    STDP_R_CR = STDP(RS, CH_R, condition='i==j')
    STDP_CL_LR = STDP(CH_L, LTS_R, stdp_type='part')
    STDP_CR_LL = STDP(CH_R, LTS_L, stdp_type='part')
    STDP_CL_LL = STDP(CH_L, LTS_L, stdp_type='part', condition='i!=j')
    STDP_CR_LR = STDP(CH_R, LTS_R, stdp_type='part', condition='i!=j')
    STDP_LL_CL = STDP(LTS_L, CH_L, stdp_type='depress', condition='i==j')
    STDP_LR_CR = STDP(LTS_R, CH_R, stdp_type='depress', condition='i==j')
    network.add([STDP_R_CL, STDP_R_CR, STDP_CL_LR, STDP_CR_LL, STDP_CL_LL, STDP_CR_LR, STDP_LL_CL, STDP_LR_CR])

    RS.I_ext[0] = 10
    network.run(2000)

    plt.figure(figsize=(12, 2 * 7))

    plt.subplot(711)
    plt.plot(LTS_L.spikes[0], np.ones(len(LTS_L.spikes[0])), 'o', markersize=3)
    plt.plot(LTS_L.record_t, LTS_L.record_v[0])
    plt.plot(LTS_L.record_t, LTS_L.record_v[1])


    plt.subplot(712)
    plt.plot(LTS_R.spikes[0], np.ones(len(LTS_R.spikes[0])), 'o', markersize=3)
    plt.plot(LTS_R.record_t, LTS_R.record_v[0])
    plt.plot(LTS_R.record_t, LTS_R.record_v[1])

    plt.subplot(713)
    plt.plot(CH_L.spikes[0], np.ones(len(CH_L.spikes[0])), 'o', markersize=3)
    plt.plot(CH_L.record_t, CH_L.record_v[0])
    plt.plot(CH_L.record_t, CH_L.record_v[1])

    plt.subplot(714)
    plt.plot(CH_R.spikes[0], np.ones(len(CH_R.spikes[0])), 'o', markersize=3)
    plt.plot(CH_R.record_t, CH_R.record_v[0])
    plt.plot(CH_R.record_t, CH_R.record_v[1])

    plt.subplot(715)
    plt.plot(RS.spikes[0], np.ones(len(RS.spikes[0])), 'o', markersize=3)
    plt.plot(RS.record_t, RS.record_v[0])
    plt.plot(RS.record_t, RS.record_v[1])

    #plt.plot(RS.record_t, RS.record_v, label='v')
    #plt.plot(CH_L.record_t, CH_L.record_v, label='n1')
    #plt.plot(CH_R.record_t, CH_R.record_v, label='n2')
    #plt.legend()
    #plt.xlabel('t (ms)')
    #plt.ylabel('spike')
