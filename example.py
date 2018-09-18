# -*- coding: utf-8 -*-
"""
Created on Fri Apr 20 14:14:45 2018

@author: zx013
"""
import os
#import numpy as np
import brian2.numpy_ as np
import matplotlib.pyplot as plt
from brian2 import *
import random

prefs.codegen.target = 'numpy'

class Poisson(PoissonGroup):
    def __init__(self, h, num=1):
        super(Poisson, self).__init__(num, h*Hz)

class Izhikevich(NeuronGroup):
    __type__ = 'neuron'

    params = \
    ((0.02,   0.2,    -65,    8), #Regular Spiking
    (0.02,    0.2,    -50,    2), #Chattering
    (0.02,    0.25,   -65,    2)) #Low-Threshod Spiking

    neuron_model = '''
    a : 1
    b : 1
    c : 1
    d : 1
    dv/dt = (0.04*v*v/mV + 5*v + 140*mV - u + I/amp*mV + I_ext/amp*mV)/ms : volt (unless refractory)
    du/dt = a*(b*v - u)/ms : volt (unless refractory)
    dI/dt = (g - I) / (5*ms) : amp
    dg/dt = -g / (5*ms) : amp
    I_ext : amp
    dp : 1
    '''
    neuron_threshold = 'v > 30*mV' #threshold不能换行
    neuron_reset = '''
    v = c*mV
    u += d*mV
    '''

    def __init__(self, spike_type='RS', num=1, *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, refractory=2*ms, method='euler')
        self.dp = 1 #是否是抑制神经元，1/-1
        if spike_type == 'RS':
            spike_choice = 0
        elif spike_type == 'CH':
            spike_choice = 1
        elif spike_type == 'LTS':
            spike_choice = 2
            self.dp = -1
        else:
            spike_choice = 0
        self.a, self.b, self.c, self.d = self.params[spike_choice]
        self.v = -65*mV
        self.u = self.b * self.v


class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    w_min = 0 : 1
    w_max = 1 : 1
    deltat : 1
    deltaw : 1
    trace : 1
    depress : 1
    forget_rate = 0.2 : 1
    rate = 0.00025 : 1
    type : 1
    '''

    #1.11*exp(-((lastspike_post - lastspike_pre)/ms + 2)**2/1.11**2) - 0.11
    #1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    #先更新lastspike再触发
    synapse_pre='''
    g_post += depress*w*amp
    deltat = (lastspike_post - lastspike_pre)/ms
    trace *= (1 - forget_rate)**abs(deltat)
    deltaw = type*(1.21*exp(-(deltat + 12.7)**2/13.61**2) - 0.21)
    trace += deltaw
    w = clip(w + rate*trace, w_min, w_max)
    type = 0
    '''
    synapse_post='''
    deltat = (lastspike_post - lastspike_pre)/ms
    trace *= (1 - forget_rate)**abs(deltat)
    deltaw = (1 - type)*(1.21*exp(-(deltat + 12.7)**2/13.61**2) - 0.21)
    trace += deltaw
    w = clip(w + rate*trace, w_min, w_max)
    type = 1
    '''

    static_model = '''
    w : 1
    depress : 1
    '''
    static_pre = '''
    g_post += depress*w*amp
    '''

    def __init__(self, source_neuron, target_neuron, wrand='rand()', static=True, part=False, *args, **kwargs):
        if static:
            super(STDP, self).__init__(source_neuron, target_neuron, self.static_model, on_pre=self.static_pre)
        else:
            super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)
        super(STDP, self).connect(n=100, *args, **kwargs)
        self.w = wrand
        if part:
            for i in range(100):
                if i % 2 == 0:
                    self.w[i] = 0
                if i % 3 == 0:
                    self.w[i] = 0
                if i % 7 == 0:
                    self.w[i] = 0

        if hasattr(source_neuron, 'dp'):
            self.depress = source_neuron.dp[0]
        else:
            self.depress = 1
        self.delay = 'rand() * 100*ms'
        if len(self.delay) == 100:
            self.delay = np.arange(100)*ms


class Monitor(StateMonitor):
    def __init__(self, node, record=True, title='', *args, **kwargs):
        self.type = 'other'
        self.title = title
        if hasattr(node, '__type__'):
            if node.__type__ == 'neuron':
                self.type = 'neuron'
                super(Monitor, self).__init__(node, 'v', record=record, *args, **kwargs)
            elif node.__type__ == 'synapse':
                self.type = 'synapse'
                super(Monitor, self).__init__(node, 'w', record=record, *args, **kwargs)
        else:
            super(Monitor, self).__init__(node, record=record, *args, **kwargs)

    def show(self):
        if self.type == 'neuron':
            for i in range(len(self.v)):
                plt.plot(self.t/ms, self.v[i]/mV, label='v%d' % i)
            plt.legend()
            plt.title(self.title)
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')
        elif self.type == 'synapse':
            plt.plot(self.t/ms, self.w[0], label='w')
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('w')
        plt.tight_layout()


class ControlCircuit:
    def __init__(self, network):
        self.RS_L = Izhikevich('RS')
        self.RS_R = Izhikevich('RS')
        network.add([self.RS_L, self.RS_R])

class DecisionCircuit:
    def __init__(self, network, num=1):
        self.CH_L = Izhikevich('CH', num=num)
        self.CH_R = Izhikevich('CH', num=num)
        self.LTS_L = Izhikevich('LTS', num=num)
        self.LTS_R = Izhikevich('LTS', num=num)
        self.RS = Izhikevich('RS', num=num)
        self.CH = Izhikevich('CH', num=num)
        network.add([self.CH_L, self.CH_R, self.LTS_L, self.LTS_R, self.RS, self.CH])

        self.stdp1 = STDP(self.CH, self.RS, j='i')
        self.stdp2 = STDP(self.RS, self.CH_L, static=False, j='i')
        self.stdp3 = STDP(self.RS, self.CH_R, static=False, j='i')
        self.stdp4 = STDP(self.CH_L, self.LTS_L, condition='j!=i')
        self.stdp5 = STDP(self.CH_L, self.LTS_R)
        self.stdp6 = STDP(self.CH_R, self.LTS_R, condition='j!=i')
        self.stdp7 = STDP(self.CH_R, self.LTS_L)
        self.stdp8 = STDP(self.LTS_L, self.CH_L, wrand='rand() + 1', part=True, j='i')
        self.stdp9 = STDP(self.LTS_R, self.CH_R, wrand='rand() + 1', part=True, j='i')
        network.add([self.stdp1, self.stdp2, self.stdp3, self.stdp4, self.stdp5, self.stdp6, self.stdp7, self.stdp8, self.stdp9])



'''
t0 = np.linspace(-15, 15, 1000)
plt.plot(t0, np.exp(-t0**2/4.5**2)*(1.2*np.exp(-t0**2/0.8**2) - 0.2))
'''
defaultclock.dt = 500.*us
if __name__ == '__main__':
    start_scope()

    network = Network()

    cc = ControlCircuit(network)
    dc = DecisionCircuit(network, num=2)

    stdp1 = STDP(dc.CH_L, cc.RS_L)
    stdp2 = STDP(dc.CH_R, cc.RS_R)
    network.add([stdp1, stdp2])

    n1 = Monitor(dc.CH_L, title='Left CH Neuron')
    n2 = Monitor(dc.CH_R, title='Right CH Neuron')
    n3 = Monitor(dc.LTS_L, title='Left LTS Neuron')
    n4 = Monitor(dc.LTS_R, title='Right LTS Neuron')
    n5 = Monitor(dc.RS, title='Input RS Neuron')
    left = Monitor(cc.RS_L, title='Output Left RS Neuron')
    right = Monitor(cc.RS_R, title='Output Right RS Neuron')

    s1 = Monitor(dc.stdp2)
    s2 = Monitor(dc.stdp3)
    s3 = Monitor(dc.stdp5)
    s4 = Monitor(dc.stdp7)

    n = [n1, n2, n3, n4, n5, left, right]
    #n = [n6, n7, n5]
    network.add(n)

    dc.CH.I_ext[0] = 5*amp
    network.run(5000*ms, report='text')

    plt.figure(figsize=(12, 2 * len(n)))

    for i in range(len(n)):
        plt.subplot(len(n) * 100 + 10 + i + 1)
        n[i].show()

    plt.show()
