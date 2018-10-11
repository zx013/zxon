#brian2.utils的单位加载时间非常长，导致import很慢
import brian2.numpy_ as np
import matplotlib.pyplot as plt
from brian2 import *
import random
from brian2tools import *
import brian2genn

set_device('genn')
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
    dv/dt = (0.04*v*v + 5*v + 140 - u + I + I_ext)/ms : 1 (unless refractory)
    du/dt = a*(b*v - u)/ms : 1 (unless refractory)
    dI/dt = (g - I) / (5*ms) : 1
    dg/dt = -g / (5*ms) : 1
    I_ext : 1
    dp : 1
    '''
    neuron_threshold = 'v > 30' #threshold不能换行
    neuron_reset = '''
    v = c
    u += d
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
        self.v = -65
        self.u = self.b * self.v


class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    w_min = 0 : 1
    w_max = 1 : 1
    depress = 1: 1
    rate = 0.0005 : 1
    dtrace/dt = (-0.223 * trace)/ms : 1 (event-driven)
    '''

    #1.11*exp(-((lastspike_post - lastspike_pre)/ms + 2)**2/1.11**2) - 0.11
    #1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    #先更新lastspike再触发
    synapse_pre='''
    g_post += depress*w
    trace += 1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    w = clip(w + rate*trace, w_min, w_max)
    '''
    synapse_post='''
    trace += 1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    w = clip(w + rate*trace, w_min, w_max)
    '''

    static_model = '''
    w : 1
    '''
    static_pre = '''
    g_post += w
    '''

    def __init__(self, source_neuron, target_neuron, wrand='100*rand()', static=True, *args, **kwargs):
        if static:
            super(STDP, self).__init__(source_neuron, target_neuron, self.static_model, on_pre=self.static_pre)
        else:
            super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)
        super(STDP, self).connect(*args, **kwargs)
        self.w = wrand


def genn():
    start_scope()

    Output_RS_L = Izhikevich('RS')
    Output_RS_R = Izhikevich('RS')

    num = 10
    Decision_CH_L = Izhikevich('CH', num=num)
    Decision_CH_R = Izhikevich('CH', num=num)
    Decision_LTS_L = Izhikevich('LTS', num=num)
    Decision_LTS_R = Izhikevich('LTS', num=num)
    Decision_RS = Izhikevich('RS', num=num)
    Decision_CH = Izhikevich('CH', num=num)

    #每个突触都会生成一个对应的文件，数量太大时会无法编译
    for i in range(1):
        STDP(Decision_CH, Decision_RS, j='i')
        STDP(Decision_RS, Decision_CH_L, j='i')
        STDP(Decision_RS, Decision_CH_R, j='i')
        STDP(Decision_CH_L, Decision_LTS_L, condition='j!=i')
        STDP(Decision_CH_L, Decision_LTS_R)
        STDP(Decision_CH_R, Decision_LTS_R, condition='j!=i')
        STDP(Decision_CH_R, Decision_LTS_L)
        wrand='- rand() - 1'
        if i % 2 == 0:
            wrand = 0
        if i % 3 == 0:
            wrand = 0
        if i % 7 == 0:
            wrand = 0
        STDP(Decision_LTS_L, Decision_CH_L, wrand, j='i')
        STDP(Decision_LTS_R, Decision_CH_R, wrand, j='i')

    STDP(Decision_CH_L, Output_RS_L)
    STDP(Decision_CH_R, Output_RS_R)

    Spike_CH_L = SpikeMonitor(Decision_CH_L)
    Spike_CH_R = SpikeMonitor(Decision_CH_R)
    Spike_LTS_L = SpikeMonitor(Decision_LTS_L)
    Spike_LTS_R = SpikeMonitor(Decision_LTS_R)
    Spike_RS = SpikeMonitor(Decision_RS)
    Spike_O_RS_L = SpikeMonitor(Output_RS_L)
    Spike_O_RS_R = SpikeMonitor(Output_RS_R)


    Decision_CH.I_ext[0] = 5
    run(1000*ms, report='text')

    plt.figure(figsize=(12, 2 * 7))

    plt.subplot(711)
    brian_plot(Spike_CH_L)
    plt.title('Left CH Neuron')

    plt.subplot(712)
    brian_plot(Spike_CH_R)
    plt.title('Right CH Neuron')

    plt.subplot(713)
    brian_plot(Spike_LTS_L)
    plt.title('Left LTS Neuron')

    plt.subplot(714)
    brian_plot(Spike_LTS_R)
    plt.title('Right LTS Neuron')

    plt.subplot(715)
    brian_plot(Spike_RS)
    plt.title('Input RS Neuron')

    plt.subplot(716)
    brian_plot(Spike_O_RS_L)
    plt.title('Output Left Neuron')

    plt.subplot(717)
    brian_plot(Spike_O_RS_R)
    plt.title('Output Right Neuron')
    #plot_raster(n1.i, n1.t)

    plt.show()


defaultclock.dt = 500.*us
if __name__ == '__main__':
    genn()