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
    ((0.02,   0.2,    -65,    8,    0), #Regular Spiking
    (0.02,    0.2,    -50,    2,    0), #Chattering
    (0.02,    0.25,   -65,    2,    0), #Low-Threshod Spiking
    (0.02,    0.2,    -65,    6,    14), #tonic spiking
    (0.02,    0.25,   -65,    6,    0.5), #phasic spiking
    (0.02,    0.2,    -50,    2,    15), #tonic bursting
    (0.02,    0.25,   -55,    0.05, 0.6), #phasic bursting
    (0.02,    0.2,    -55,    4,    10), #mixed mode
    (0.01,    0.2,    -65,    8,    30), #spike frequency adaptation
    (0.02,    -0.1,   -55,    6,    0), #Class 1
    (0.2,     0.26,   -65,    0,    0), #Class 2
    (0.02,    0.2,    -65,    6,    7), #spike latency
    (0.05,    0.26,   -60,    0,    0), #subthreshold oscillations
    (0.1,     0.26,   -60,    -1,   0), #resonator
    (0.02,    -0.1,   -55,    6,    0), #integrator
    (0.03,    0.25,   -60,    4,    0), #rebound spike
    (0.03,    0.25,   -52,    0,    0), #rebound burst
    (0.03,    0.25,   -60,    4,    0), #threshold variability
    (1,       1.5,    -60,    0,    -65), #bistability
    (1,       0.2,    -60,    -21,  0), #DAP
    (0.02,    1,      -55,    4,    0), #accomodation
    (-0.02,   -1,     -60,    8,    80), #inhibition-induced spiking
    (-0.026,  -1,     -45,    -8,    80)) #inhibition-induced bursting, d(0 -> -8)

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
        self.v = -70*mV
        self.u = -14*mV
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
        self.a, self.b, self.c, self.d, _ = self.params[spike_choice]


class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    w_max = 1 : 1
    deltaw : 1
    depress : 1
    rate = 0.01 : 1
    type : 1
    '''
    #1.11*exp(-((tpost - tpre)/ms + 2)**2/1.11**2) - 0.11
    #1.21*exp(-((tpost - tpre)/ms + 12.7)**2/13.61**2) - 0.21
    #先更新lastspike再触发
    synapse_pre='''
    g_post += depress*w*amp
    deltaw = type*(1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21)
    w = clip(w + rate*deltaw, 0, w_max)
    type = 0
    '''
    synapse_post='''
    deltaw = (1 - type)*(1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21)
    w = clip(w + rate*deltaw, 0, w_max)
    type = 1
    '''

    def __init__(self, source_neuron, target_neuron, *args, **kwargs):
        super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)
        super(STDP, self).connect(n=100, *args, **kwargs)
        self.w = 'rand()'
        if hasattr(source_neuron, 'dp'):
            self.depress = source_neuron.dp[0]
        else:
            self.depress = 1
        self.delay = 'rand() * 100*ms'


class Monitor(StateMonitor):
    def __init__(self, node, record=True, *args, **kwargs):
        self.type = 'other'
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
            plt.title('sub %d' % i)
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')
        elif self.type == 'synapse':
            plt.plot(self.t/ms, self.w[0], label='w')
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('w')


class SensingCircuit:
    def __init__(self, network):
        self.CH = Izhikevich('CH')
        network.add(self.CH)

class PunishmentCircuit:
    def __init__(self, network):
        self.CH = Izhikevich('CH')
        network.add(self.CH)

class ControlCircuit:
    def __init__(self, network):
        self.RS_L = Izhikevich('RS')
        self.RS_R = Izhikevich('RS')
        network.add([self.RS_L, self.RS_R])

class DecisionCircuit:
    def __init__(self, network):
        self.CH_L = Izhikevich('CH')
        self.CH_R = Izhikevich('CH')
        self.LTS_L = Izhikevich('LTS')
        self.LTS_R = Izhikevich('LTS')
        self.RS = Izhikevich('RS')
        self.LTS = Izhikevich('LTS')
        network.add([self.CH_L, self.CH_R, self.LTS_L, self.LTS_R, self.RS, self.LTS])

        self.stdp1 = STDP(self.LTS, self.RS, j='i')
        self.stdp2 = STDP(self.RS, self.CH_L, j='i')
        self.stdp3 = STDP(self.RS, self.CH_R, j='i')
        self.stdp4 = STDP(self.CH_L, self.LTS_L, condition='j!=i')
        self.stdp5 = STDP(self.CH_L, self.LTS_R)
        self.stdp6 = STDP(self.CH_R, self.LTS_R, condition='j!=i')
        self.stdp7 = STDP(self.CH_R, self.LTS_L)
        self.stdp8 = STDP(self.LTS_L, self.CH_L, j='i')
        self.stdp9 = STDP(self.LTS_R, self.CH_R, j='i')
        network.add([self.stdp1, self.stdp2, self.stdp3, self.stdp4, self.stdp5, self.stdp6, self.stdp7, self.stdp8, self.stdp9])


class Fly:
    def __init__(self):
        pass


'''
t0 = np.linspace(-15, 15, 1000)
plt.plot(t0, np.exp(-t0**2/4.5**2)*(1.2*np.exp(-t0**2/0.8**2) - 0.2))
'''
defaultclock.dt = 500.*us
if __name__ == '__main__':
    start_scope()

    network = Network()

    sc = SensingCircuit(network)
    pc = PunishmentCircuit(network)
    cc = ControlCircuit(network)
    dc = DecisionCircuit(network)

    stdp1 = STDP(sc.CH, dc.RS, j='i')
    stdp2 = STDP(pc.CH, dc.LTS)
    stdp3 = STDP(pc.CH, dc.CH_L)
    stdp4 = STDP(pc.CH, dc.CH_R)
    stdp5 = STDP(dc.CH_L, cc.RS_L)
    stdp6 = STDP(dc.CH_R, cc.RS_R)
    network.add([stdp1, stdp2, stdp3, stdp4, stdp5, stdp6])

    n1 = Monitor(dc.CH_L)
    n2 = Monitor(dc.CH_R)
    n3 = Monitor(dc.LTS_L)
    n4 = Monitor(dc.LTS_R)
    n5 = Monitor(dc.RS)
    n6 = Monitor(pc.CH)
    n7 = Monitor(dc.LTS)
    #left = Monitor(cc.RS_L)
    #right = Monitor(cc.RS_R)

    s2 = Monitor(dc.stdp2)
    s4 = Monitor(dc.stdp3)
    s5 = Monitor(dc.stdp5)
    s6 = Monitor(dc.stdp7)

    n = [n1, n2, n3, n4, n5, s2, s4, s5, s6]
    #n = [n6, n7, n5]
    network.add(n)

    sc.CH.I_ext[0] = 5*amp
    #dc.RS.I_ext[0] = 10*amp
    pc.CH.I_ext = 0*amp
    network.run(1000*ms, report='text')

    pc.CH.I_ext = 5*amp
    network.run(1000*ms, report='text')

    pc.CH.I_ext = 0*amp
    network.run(1000*ms, report='text')

    plt.figure(figsize=(12, 2 * len(n)))

    for i in range(len(n)):
        plt.subplot(len(n) * 100 + 10 + i + 1)
        n[i].show()

    plt.show()
