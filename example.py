# -*- coding: utf-8 -*-
"""
Created on Fri Apr 20 14:14:45 2018

@author: zx013
"""
from brian2 import *
import matplotlib.pyplot as plt

prefs.codegen.target = 'numpy'

def cobahh():
    area = 20000*umetre**2
    Cm = (1*ufarad*cm**-2) * area
    gl = (5e-5*siemens*cm**-2) * area

    El = -60*mV
    EK = -90*mV
    ENa = 50*mV
    g_na = (100*msiemens*cm**-2) * area
    g_kd = (30*msiemens*cm**-2) * area
    VT = -63*mV

    taue = 5*ms
    taui = 10*ms

    Ee = 0*mV
    Ei = -80*mV

    we = 6*nS
    wi = 67*nS

    eqs = Equations('''
                    dv/dt = (gl*(El - v) + ge*(Ee - v) + gi*(Ei - v) - g_na*(m*m*m)*h*(v - ENa) - g_kd*(n*n*n*n)*(v - EK))/Cm : volt
                    dm/dt = alpha_m*(1 - m) - beta_m*m : 1
                    dn/dt = alpha_n*(1 - n) - beta_n*n : 1
                    dh/dt = alpha_h*(1 - h) - beta_h*h : 1
                    dge/dt = -ge*(1./taue) : siemens
                    dgi/dt = -gi*(1./taui) : siemens
                    alpha_m = 0.32*(mV**-1)*(13*mV - v + VT)/(exp((13*mV - v + VT)/(4*mV)) - 1.)/ms : Hz
                    beta_m = 0.28*(mV**-1)*(v - VT - 40*mV)/(exp((v - VT - 40*mV)/(5*mV)) - 1)/ms : Hz
                    alpha_n = 0.032*(mV**-1)*(15*mV - v + VT)/(exp((15*mV - v + VT)/(5*mV)) - 1.)/ms : Hz
                    beta_n = .5*exp((10*mV - v + VT)/(40*mV))/ms : Hz
                    alpha_h = 0.128*exp((17*mV - v + VT)/(18*mV))/ms : Hz
                    beta_h = 4./(1 + exp((40*mV - v + VT)/(5*mV)))/ms : Hz
                    ''')

    P = NeuronGroup(4000, model=eqs, threshold='v > -20*mV', refractory=3*ms, method='exponential_euler')
    Pe = P[:3200]
    Pi = P[3200:]
    Ce = Synapses(Pe, P, on_pre='ge += we')
    Ci = Synapses(Pi, P, on_pre='gi += wi')
    Ce.connect(p=0.02)
    Ci.connect(p=0.02)

    P.v = 'El + (randn()*5 - 5)*mV'
    P.ge = '(randn()*1.5 + 4)*10.*nS'
    P.gi = '(randn()*12 + 20)*10.*nS'

    trace = StateMonitor(P, 'v', record=[1, 10, 100])

    run(100*ms, report='text')

    plt.plot(trace.t/ms, trace[1].v/mV)
    plt.plot(trace.t/ms, trace[10].v/mV)
    plt.plot(trace.t/ms, trace[100].v/mV)
    plt.xlabel('t (ms)')
    plt.ylabel('v (mV)')
    plt.show()

pars = ((0.02,    0.2,    -65,    6,    14), #tonic spiking
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

def Izhikevich():
    start_scope()

    a, b, c, d, I = pars[15]

    model = '''
    dv/dt = (0.04*v*v + 5*v + 140 - u + I)/ms : 1 (unless refractory)
    du/dt = (a*(b*v - u))/ms : 1 (unless refractory)
    '''
    threshold = 'v > 30' #threshold不能换行
    reset = '''
    v = c
    u += d
    '''
    #P = PoissonGroup(1, 0*Hz)
    G = NeuronGroup(1, model, threshold=threshold, reset=reset)
    G.v = -70
    G.u = -20

    #S = Synapses(P, G, on_pre='v += 10')
    #S.connect(j='i')

    state_monitor = StateMonitor(G, ['v', 'u'], record=True)

    run(100*ms, report='text')

    plt.plot(state_monitor.t/ms, state_monitor[0].v)
    #plt.plot(state_monitor.t/ms, state_monitor[0].u)
    plt.xlabel('t (ms)')
    plt.ylabel('v (mV)')
    plt.show()

if __name__ == '__main__':
    Izhikevich()