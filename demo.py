# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 13:26:05 2018

@author: zx013
"""

import os
import struct
import pickle
import functools
import numpy as np
import matplotlib.pyplot as plt
from brian2 import *

prefs.codegen.target = 'numpy'

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
    I = 0*amp : amp
    '''
    neuron_threshold = 'v > 30*mV' #threshold不能换行
    neuron_reset = '''
    v = c*mV
    u += d*mV
    '''
    
    def __init__(self, num=1, inhibition=False, *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, method='euler')
        self.v = -70*mV
        self.u = -20*mV
        self.a, self.b, self.c, self.d, _ = self.params[18 if inhibition else 0]

class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    wmax = 1 : 1
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
        self.w = 'rand()*wmax'
        return

        if os.path.isfile(self.cache):
            self.w = np.load(self.cache)
        else:
            self.w = 'rand()*wmax'

    def save(self):
        np.save(self.cache, self.w)

    def load(self):
        self.w = np.load(self.cache)


MNIST_data_path  = 'data/'

def get_labeled_data(test):
    if test:
        picklename = 'test.pickle'
    else:
        picklename = 'train.pickle'

    if os.path.isfile(picklename):
        data = pickle.load(open(picklename, 'rb'))
    else:
        if test:
            images = open(MNIST_data_path + 't10k-images.idx3-ubyte', 'rb')
            labels = open(MNIST_data_path + 't10k-labels.idx1-ubyte', 'rb')
        else:
            images = open(MNIST_data_path + 'train-images.idx3-ubyte', 'rb')
            labels = open(MNIST_data_path + 'train-labels.idx1-ubyte', 'rb')

        images.read(4)
        num = struct.unpack('>I', images.read(4))[0]
        rows = struct.unpack('>I', images.read(4))[0]
        cols = struct.unpack('>I', images.read(4))[0]

        labels.read(4)
        N = struct.unpack('>I', labels.read(4))[0]

        if num != N:
            raise Exception('Error')

        x = np.zeros((N, rows, cols), dtype=np.uint8)
        y = np.zeros((N, 1), dtype=np.uint8)

        for i in range(N):
            x[i] = [[struct.unpack('>B', images.read(1))[0] for col in range(cols)] for row in range(rows)]
            y[i] = struct.unpack('>B', labels.read(1))[0]
        data = {'x': x, 'y': y, 'rows': rows, 'cols': cols}

        pickle.dump(data, open(picklename, 'wb'))
    return data

def learn_data(data, num, rows, cols):
    pass

if __name__ == '__main__':
    start_scope()
    data = get_labeled_data(False)
    num = data['rows'] * data['cols']

    poisson = PoissonGroup(num, [0]*num*Hz)
    izh1 = Izhikevich(400, False)
    izh2 = Izhikevich(400, True)
    
    stdp1 = STDP(poisson, izh1)
    stdp2 = STDP(izh1, izh2)
    stdp1.connect()
    stdp2.connect(j='i')

    net = Network([poisson, izh1, izh2, stdp1, stdp2])

    for i in range(len(data['x'])):
        poisson.rates = functools.reduce(lambda x, y: np.append(x, y), data['x'][i])*Hz
        net.run(350*ms, report='text')
        poisson.rates = 0*Hz
        net.run(150*ms, report='text')
        #learn_data(data['x'][i], data['y'][i], rows, cols)