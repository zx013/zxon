# -*- coding: utf-8 -*-
"""
Created on Fri Apr 20 14:14:45 2018

@author: zx013
"""
import os
import numpy as np
import matplotlib.pyplot as plt
from brian2 import PoissonGroup, NeuronGroup, Synapses, StateMonitor
from brian2 import Hz, ms, prefs, start_scope, run

prefs.codegen.target = 'numpy'

class Poisson(PoissonGroup):
    def __init__(self, h, num=1):
        super(Poisson, self).__init__(num, h*Hz)

class Izhikevich(NeuronGroup):
    __type__ = 'neuron'

    params = \
    ((0.02,    0.2,    -65,    6,    14), #tonic spiking
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
    (-0.026,  -1,     -45,    0,    80)) #inhibition-induced bursting

    neuron_model = '''
    a : 1
    b : 1
    c : 1
    d : 1
    I : 1
    dv/dt = (0.04*v*v + 5*v + 140 - u + I)/ms : 1
    du/dt = (a*(b*v - u))/ms : 1
    '''
    neuron_threshold = 'v > 30' #threshold不能换行
    neuron_reset = '''
    v = c
    u += d
    '''
    
    def __init__(self, num=1, *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, method='euler')
        self.v = -70
        self.u = -20
        self.a, self.b, self.c, self.d, _ = self.params[0]
        self.I = 0

class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    wmax : 1
    taupre : second
    taupost : second
    apre : 1
    apost : 1
    ratepre : 1
    ratepost : 1
    dpre/dt = -pre/taupre : 1 (event-driven)
    dpost/dt = -post/taupost : 1 (event-driven)
    '''
    synapse_pre='''
    v_post += w
    pre += apre
    w = clip(w + ratepost*post, 0, wmax)
    '''
    synapse_post='''
    post += apost
    w = clip(w + ratepre*pre, 0, wmax)
    '''
    
    cache = 'stdp.npy'

    def __init__(self, source_neuron, target_neuron, *args, **kwargs):
        super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)

    def connect(self, *args, **kwargs):
        super(STDP, self).connect(*args, **kwargs)
        self.wmax = 1
        self.taupre = self.taupost = 20*ms
        self.apre = 0.01 * self.wmax
        self.apost = -self.apre * self.taupre / self.taupost * 1.05
        self.ratepre = 0.01
        self.ratepost = 1

        if os.path.isfile(self.cache):
            stdp.w = np.load(self.cache)
        else:
            stdp.w = 'rand()*wmax'

    def save(self):
        np.save(self.cache, stdp.w)

    def load(self):
        stdp.w = np.load(self.cache)

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
            plt.plot(self.t/ms, self.v[num], label='v%d' % num)
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')
        elif self.type == 'synapse':
            plt.plot(self.t/ms, self.w[num], label='w%d' % num)
            plt.legend()
            plt.xlabel('t (ms)')
            plt.ylabel('v (mV)')


if __name__ == '__main__':
    start_scope()
    poisson = Poisson(50, num=100)
    izh = Izhikevich(100)
    stdp = STDP(poisson, izh)
    stdp.connect()

    neuron_monitor = Monitor(izh)
    synapse_monitor = Monitor(stdp)

    run(10000*ms, report='text')
    stdp.save()

    plt.figure(figsize=(4, 8))
    plt.subplot(211)
    neuron_monitor.show()

    plt.subplot(212)
    synapse_monitor.show(0)
    synapse_monitor.show(1)

    plt.show()