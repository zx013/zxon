from brian2 import *
import brian2genn
set_device('genn')

N = 25
tau_input = 5*ms

# Noisy neurons receiving the same deterministic input
tau = 10*ms
sigma = .015
eqs_neurons = '''
dI/dt= -I / tau_input : 1
dx/dt = (0.9 + .5 * I - x) / tau : 1
'''
neurons = NeuronGroup(N, model=eqs_neurons, threshold='x > 1',
                      reset='x = 0', refractory=5*ms)
neurons.x = 'rand()'
spikes = SpikeMonitor(neurons)

run(500*ms)