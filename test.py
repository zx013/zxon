from brian2 import *
import matplotlib.pyplot as plt

if __name__ == '__main__':
    start_scope()

    N = 1
    tau_v = 10*ms
    tau_active = 10*ms
    
    #not_refractory，在不应期时为0，不在不应期时为1
    eqs = '''dv/dt = (1 - v)/tau_v : 1 (unless refractory)
    dw/dt = (-w / tau_active)*int(not_refractory) : 1'''

    G = NeuronGroup(N, eqs, threshold='v > 0.6', reset='v = 0; w += 0.1', refractory=5*ms)
    M = StateMonitor(G, ['v', 'w'], record=0)
    
    P = NeuronGroup(10, '')
    Q = NeuronGroup(10, '')
    S = Synapses(P, Q, '''w : 1''')
    S.connect(j='i if i % 2 == 0')

    net = Network(G)
    run(100*ms)

    plt.plot(M.t / ms, M.v[0])
    plt.plot(M.t / ms, M.w[0])
    plt.xlabel('Time (ms)')
    plt.ylabel('v')