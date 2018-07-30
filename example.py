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
    dv/dt = (0.04*v*v/mV + 5*v + 140*mV - u + I/amp*mV)/ms : volt (unless refractory)
    du/dt = a*(b*v - u)/ms : volt (unless refractory)
    dI/dt = (g - I) / (5*ms) : amp
    dg/dt = -g / (5*ms) : amp
    dp : 1
    '''
    neuron_threshold = 'v > 30*mV' #threshold不能换行
    neuron_reset = '''
    v = c*mV
    u += d*mV
    '''

    def __init__(self, num=1, spike_type='RS', *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, refractory=5*ms, method='euler')
        self.v = -70*mV
        self.u = -20*mV
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
    deltaw : 1
    tpre : second
    tpost : second
    type : 1
    depress : 1
    '''
    #w += 1.11*exp(-((tpost - tpre)/ms + 2)**2/1.11**2) - 0.11
    synapse_pre='''
    tpre = t
    deltaw = type*(1.21*exp(-((tpost - tpre)/ms + 12.7)**2/13.61**2) - 0.21)
    w = clip(w + deltaw, 0, 10)
    g_post += 10*depress*w*amp
    type = 0
    '''
    synapse_post='''
    tpost = t
    deltaw = (1 - type)*(1.21*exp(-((tpost - tpre)/ms + 12.7)**2/13.61**2) - 0.21)
    w = clip(w + deltaw, 0, 10)
    g_post += 10*depress*w*amp
    type = 1
    '''

    def __init__(self, source_neuron, target_neuron, *args, **kwargs):
        super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)
        super(STDP, self).connect(*args, **kwargs)
        if hasattr(source_neuron, 'dp'):
            self.depress = source_neuron.dp
        else:
            self.depress = 1


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

    def show(self, num=0):
        if self.type == 'neuron':
            plt.plot(self.t/ms, self.v[num]/mV, label='v%d' % num)
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')
        elif self.type == 'synapse':
            plt.plot(self.t/ms, self.w[num], label='w%d' % num)
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')


class SensingCircuit:
    def __init__(self, network):
        self.CH_BL = Izhikevich(1, 'CH')
        self.CH_GL = Izhikevich(1, 'CH')
        self.CH_BR = Izhikevich(1, 'CH')
        self.CH_GR = Izhikevich(1, 'CH')
        network.add([self.CH_BL, self.CH_GL, self.CH_BR, self.CH_GR])

class PunishmentCircuit:
    def __init__(self, network):
        self.CH = Izhikevich(1, 'CH')
        network.add(self.CH)

class ControlCircuit:
    def __init__(self, network):
        self.RS_left = Izhikevich(1, 'RS')
        self.RS_right = Izhikevich(1, 'RS')
        network.add([self.RS_left, self.RS_right])

class DecisionCircuit:
    def __init__(self, network):
        self.CH_left = Izhikevich(1, 'CH')
        self.CH_right = Izhikevich(1, 'CH')
        self.LTS_left = Izhikevich(1, 'LTS')
        self.LTS_right = Izhikevich(1, 'LTS')
        self.RS = Izhikevich(1, 'RS')
        self.LTS = Izhikevich(1, 'LTS')

        network.add([self.CH_left, self.CH_right, self.LTS_left, self.LTS_right, self.RS, self.LTS])

        self.stdp1 = STDP(self.LTS, self.RS)
        self.stdp2 = STDP(self.RS, self.CH_left)
        self.stdp3 = STDP(self.RS, self.CH_right)
        self.stdp4 = STDP(self.CH_left, self.LTS_right)
        self.stdp5 = STDP(self.CH_right, self.LTS_left)
        self.stdp6 = STDP(self.LTS_left, self.CH_left)
        self.stdp7 = STDP(self.LTS_right, self.CH_right)
        network.add([self.stdp1, self.stdp2, self.stdp3, self.stdp4, self.stdp5, self.stdp6, self.stdp7])


class Fly:
    def __init__(self):
        pass


if __name__ == '__main__':
    start_scope()

    network = Network()
    poisson = Poisson(50)
    network.add(poisson)

    sc = SensingCircuit(network)
    pc = PunishmentCircuit(network)
    cc = ControlCircuit(network)
    dc = DecisionCircuit(network)

    stdp1 = STDP(poisson, sc.CH_BL)
    stdp2 = STDP(sc.CH_BL, dc.RS)
    stdp3 = STDP(pc.CH, dc.LTS)
    stdp4 = STDP(pc.CH, dc.CH_left)
    stdp5 = STDP(pc.CH, dc.CH_right)
    stdp6 = STDP(dc.CH_left, cc.RS_left)
    stdp7 = STDP(dc.CH_right, cc.RS_right)
    network.add([stdp1, stdp2, stdp3, stdp4, stdp5, stdp6, stdp7])

    #left = Monitor(cc.RS_left)
    #right = Monitor(cc.RS_right)
    n1 = Monitor(sc.CH_BL)
    n2 = Monitor(dc.RS)
    n3 = Monitor(dc.CH_left)
    n4 = Monitor(dc.CH_right)
    n5 = Monitor(dc.LTS_left)
    n6 = Monitor(dc.LTS_right)
    s1 = Monitor(dc.stdp6)
    s2 = Monitor(dc.stdp7)

    n = [n1, n2, n3, n4, n5, n6, s1, s2]
    network.add(n)
    network.run(500*ms, report='text')

    plt.figure(figsize=(4, 2 * len(n)))

    for i in range(len(n)):
        plt.subplot(len(n) * 100 + 10 + i + 1)
        n[i].show()

    plt.show()
