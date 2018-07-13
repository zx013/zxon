# -*- coding: utf-8 -*-
"""
Created on Fri Apr 20 14:14:45 2018

@author: zx013
"""
import os
#import numpy as np
import brian2.numpy_ as np
import matplotlib.pyplot as plt
from brian2 import PoissonGroup, NeuronGroup, Synapses, StateMonitor
from brian2 import Hz, ms, mV, mA, nA, amp, prefs, start_scope, run

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
    '''
    neuron_threshold = 'v > 30*mV' #threshold不能换行
    neuron_reset = '''
    v = c*mV
    u += d*mV
    '''
    
    def __init__(self, num=1, spike_type='RS', *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, method='euler')
        self.v = -70*mV
        self.u = -20*mV
        if spike_type == 'RS':
            spike_choice = 0
        elif spike_type == 'CH':
            spike_choice = 1
        elif spike_type == 'LTS':
            spike_choice = 2
        else:
            spike_choice = 0
        self.a, self.b, self.c, self.d, _ = self.params[spike_choice]

class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    tpre : second
    tpost : second
    type : 1
    '''
    #w += 1.11*exp(-((tpost - tpre)/ms + 2)**2/1.11**2) - 0.11
    synapse_pre='''
    tpre = t
    w = type*(1.21*exp(-((tpost - tpre)/ms + 12.7)**2/13.61**2) - 0.21)
    g_post += w*amp
    type = 0
    '''
    synapse_post='''
    tpost = t
    w = (1 - type)*(1.21*exp(-((tpost - tpre)/ms + 12.7)**2/13.61**2) - 0.21)
    g_post += w*amp
    type = 1
    '''
    
    cache = 'stdp.npy'

    def __init__(self, source_neuron, target_neuron, *args, **kwargs):
        super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)

    def connect(self, *args, **kwargs):
        super(STDP, self).connect(*args, **kwargs)

        #if os.path.isfile(self.cache):
        #    self.w = np.load(self.cache)
        #else:
        #    self.w = 'rand()*wmax'

    def save(self):
        np.save(self.cache, self.w)

    def load(self):
        self.w = np.load(self.cache)

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


if __name__ == '__main__':
    start_scope()

    poisson = Poisson(50, 200)
    izh = Izhikevich(100)
    stdp = STDP(poisson, izh)
    stdp.connect()

    neuron_monitor = Monitor(izh)
    synapse_monitor = Monitor(stdp)

    run(100*ms, report='text')

    plt.figure(figsize=(4, 8))
    plt.subplot(211)
    neuron_monitor.show()

    plt.subplot(212)
    synapse_monitor.show()

    plt.show()
    