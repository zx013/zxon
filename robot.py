# -*- coding: utf-8 -*-
"""
Created on Wed Sep 26 13:24:31 2018

@author: zx013
"""
import numpy as np
import matplotlib.pyplot as plt

class Izhikevich:
    params = {
        'RS': (0.02,   0.2,    -65,    8), #Regular Spiking
        'CH': (0.02,    0.2,    -50,    2), #Chattering
        'LTS': (0.02,    0.25,   -65,    2) #Low-Threshod Spiking
    } 
    
    def __init__(self, spike_type='RS', *args, **kwargs):
        self.spike_type = spike_type
        self.a, self.b, self.c, self.d = self.params[spike_type]
        self.v = -65
        self.u = self.b * self.v
        self.I = 0
        self.g = 0
        self.I_ext = 0
        
        self.lastspike = 0
        self.t = 0
        
        self.record_t = np.zeros(0)
        self.record_v = np.zeros(0)
        #self.record_spike = np.zeros(0)
        self.record()
        
        self.stdp = []

    def init(self):
        self.v = -65
        self.u = self.b * self.v
        self.I = 0

    def spike(self):
        self.lastspike = self.t
        for stdp in self.stdp:
            stdp.spike()

    def next(self):
        self.t += 1

        step = 2
        for i in range(step):
            self.v += (0.04 * self.v ** 2 + 5 * self.v + 140 - self.u + self.I + self.I_ext) / step
            self.u += self.a * (self.b * self.v - self.u) / step
            self.I += (self.g - self.I) / 5 / step #把psp转换成微分方程形式
            self.g += - self.g / 5 / step
        if self.v > 30:
            self.v = self.c
            self.u += self.d
            self.spike()
        self.record()

    def record(self):
        self.record_t = np.append(self.record_t, self.t)
        self.record_v = np.append(self.record_v, self.v)

    def connect(self, izh):
        self.stdp.append(STDP(self, izh))


class STDP:
    def __init__(self, izh_pre, izh_post, num=100, rate=0, spike_type='RS'):
        self.izh_pre = izh_pre
        self.izh_post = izh_post #突触连接到的神经元
        self.num = num
        
        self.rate = rate
        self.trace = np.zeros(num)
        if spike_type == 'LTS': #LTS -> CH
            self.w = -1 - np.random.rand(1, 100)[0]
        else:
            self.w = np.random.rand(1, 100)[0]
            if spike_type == 'CH': #CH -> LTS
                for i in range(num):
                    if (i % 2 == 0) or (i % 3 == 0) or (i % 7 == 0):
                        self.w[i] = 0
        self.delay = np.arange(num)

    def spike(self):
        self.izh_post.g += sum(self.w * np.exp(- self.delay / 5))

        self.trace *= 0.8 #遗忘速率
        delta = self.izh_post.lastspike - self.izh_pre.lastspike + self.delay
        self.trace += 1.21 * np.exp(-(delta + 12.7) ** 2 / 13.61 ** 2) - 0.21
        self.w = np.clip(self.w + self.rate * self.trace, 0, 1)
            

if __name__ == '__main__':
    izh = Izhikevich('RS')
    izh_next = Izhikevich('CH')

    izh.connect(izh_next)
    izh.I_ext = 10
    for i in range(500):
        izh.next()
        izh_next.next()
    
    plt.plot(izh.record_t, izh.record_v, label='v')
    plt.plot(izh_next.record_t, izh_next.record_v, label='n')
    plt.legend()
    plt.xlabel('t (ms)')
    plt.ylabel('v (mV)')
