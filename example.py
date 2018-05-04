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

class HodgkinHuxley(NeuronGroup):
    __type__ = 'neuron'
    
    neuron_model = '''
    area = 20000*umetre**2 : metre**2
    Cm = 1*ufarad*cm**-2*area : farad
    ENa = 50*mV : volt
    EK = -90*mV : volt
    El = -65*mV : volt
    g_na = 100*msiemens*cm**-2*area : siemens
    g_kd = 30*msiemens*cm**-2*area : siemens
    gl = 5e-5*siemens*cm**-2*area : siemens
    VT = -63*mV : volt
    dv/dt = (gl*(El-v) - g_na*(m*m*m)*h*(v-ENa) - g_kd*(n*n*n*n)*(v-EK) + I)/Cm : volt
    dm/dt = 0.32*(mV**-1)*(13.*mV-v+VT)/(exp((13.*mV-v+VT)/(4.*mV))-1.)/ms*(1-m)-0.28*(mV**-1)*(v-VT-40.*mV)/
(exp((v-VT-40.*mV)/(5.*mV))-1.)/ms*m : 1
    dn/dt = 0.032*(mV**-1)*(15.*mV-v+VT)/(exp((15.*mV-v+VT)/(5.*mV))-1.)/ms*(1.-n)-.5*exp((10.*mV-v+VT)/(40.*mV))/ms*n : 1
    dh/dt = 0.128*exp((17.*mV-v+VT)/(18.*mV))/ms*(1.-h)-4./(1+exp((40.*mV-v+VT)/(5.*mV)))/ms*h : 1
    I : amp
    '''
    neuron_threshold = 'v > 0*mV'
    neuron_reset = ''
    
    def __init__(self, num=1, *args, **kwargs):
        super(HodgkinHuxley, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, method='exponential_euler')
        self.v = -70*mV
        self.I = 0.1*nA

class LeakyIF(NeuronGroup):
    __type__ = 'neuron'
    
    neuron_model = '''
    tau = 10*ms : second
    dv/dt = -v/tau + I*ohm/ms : volt (unless refractory)
    I : amp
    '''
    neuron_threshold = 'v > 10*mV'
    neuron_reset = 'v = -70*mV'
    neuron_refractory = 10*ms
    
    def __init__(self, num=1, *args, **kwargs):
        super(LeakyIF, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, refractory=self.neuron_refractory, method='exponential_euler')
        self.v = -70*mV
        self.I = 2*mA

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
    (-0.026,  -1,     -45,    -8,    80)) #inhibition-induced bursting, d(0 -> -8)

    neuron_model = '''
    a : 1
    b : 1
    c : 1
    d : 1
    dv/dt = (0.04*v*v/mV + 5*v + 140*mV - u + I/amp*mV)/ms : volt (unless refractory)
    du/dt = a*(b*v - u)/ms : volt
    I : amp
    '''
    neuron_threshold = 'v > 30*mV' #threshold不能换行
    neuron_reset = '''
    v = c*mV
    u += d*mV
    '''
    
    def __init__(self, num=1, *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, method='euler')
        self.v = -70*mV
        self.u = -20*mV
        self.a, self.b, self.c, self.d, _ = self.params[0]
        self.I = 0*amp

class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    wmax = 10 : 1
    taupre = 20*ms : second
    taupost = taupre : second
    apre = 0.01 * wmax : 1
    apost = -apre * taupre / taupost * 1.05 : 1
    ratepre = 0.01 : 1
    ratepost = 0.01 : 1
    dpre/dt = -pre/taupre : 1 (event-driven)
    dpost/dt = -post/taupost : 1 (event-driven)
    '''
    synapse_pre='''
    v_post += w*mV
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

        if os.path.isfile(self.cache):
            self.w = np.load(self.cache)
        else:
            self.w = 'rand()*wmax'

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
    poisson = Poisson(15, 100)
    izh = Izhikevich(100)
    stdp = STDP(poisson, izh)
    stdp.connect()

    neuron_monitor = Monitor(izh)
    synapse_monitor = Monitor(stdp)

    run(100*ms, report='text')
    stdp.save()

    plt.figure(figsize=(4, 8))
    plt.subplot(211)
    neuron_monitor.show()

    plt.subplot(212)
    synapse_monitor.show()

    plt.show()