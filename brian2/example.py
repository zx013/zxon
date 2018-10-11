# -*- coding: utf-8 -*-
"""
Created on Fri Apr 20 14:14:45 2018

@author: zx013
"""
import os
import brian2.numpy_ as np
import matplotlib.pyplot as plt
from brian2 import Hz, ms, us
from brian2 import prefs, defaultclock, start_scope
from brian2 import Network, PoissonGroup, NeuronGroup, Synapses, SpikeMonitor, StateMonitor
from brian2tools import brian_plot
#from numba import cuda
#import brian2genn

#set_device('genn')
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
    total_I = clip(e*I + I_ext, -20, 40) : 1
    dv/dt = (0.04*v*v + 5*v + 140 - u + total_I)/ms : 1 (unless refractory)
    du/dt = a*(b*v - u)/ms : 1 (unless refractory)
    dI/dt = (g - I) / (5*ms) : 1
    dg/dt = -g / (5*ms) : 1
    I_ext : 1
    type : 1
    '''
    neuron_threshold = 'v > 30' #threshold不能换行
    neuron_reset = '''
    v = c
    u += d
    '''

    def __init__(self, spike_type='RS', num=1, *args, **kwargs):
        super(Izhikevich, self).__init__(num, self.neuron_model, threshold=self.neuron_threshold, reset=self.neuron_reset, refractory=0*ms, method='euler')
        if spike_type == 'RS':
            spike_choice = 0
        elif spike_type == 'CH':
            spike_choice = 1
        elif spike_type == 'LTS':
            spike_choice = 2
        else:
            spike_choice = 0
        self.type = spike_choice
        self.a, self.b, self.c, self.d = self.params[spike_choice]
        self.reset()

    def reset(self):
        self.v = -65
        self.u = self.b * self.v
        self.I = 0
        self.g = 0
        if self.type[0] == 1:
            self.I_ext = '0.5*rand()'


class STDP(Synapses):
    __type__ = 'synapse'

    synapse_model = '''
    w : 1
    w_min = 0 : 1
    w_max = 1 : 1
    rate : 1
    dtrace/dt = (-0.223 * trace)/ms : 1 (event-driven)
    '''

    #1.11*exp(-((lastspike_post - lastspike_pre)/ms + 2)**2/1.11**2) - 0.11
    #1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    #先更新lastspike再触发
    synapse_pre='''
    g_post += w
    trace += 1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    w = clip(w + rate*trace, w_min, w_max)
    '''
    synapse_post='''
    trace += 1.21*exp(-((lastspike_post - lastspike_pre)/ms + 12.7)**2/13.61**2) - 0.21
    w = clip(w + rate*trace, w_min, w_max)
    '''

    static_model = '''
    w : 1
    rate : 1
    '''
    static_pre = '''
    g_post += w
    '''

    def __init__(self, source_neuron, target_neuron, num=100, wrand='rand()', static=True, part=False, *args, **kwargs):
        if static:
            super(STDP, self).__init__(source_neuron, target_neuron, self.static_model, on_pre=self.static_pre)
        else:
            super(STDP, self).__init__(source_neuron, target_neuron, self.synapse_model, on_pre=self.synapse_pre, on_post=self.synapse_post)
        super(STDP, self).connect(n=num, *args, **kwargs)
        self.w = wrand
        _index = int(len(self.w) / num)
        if part:
            _w = np.ones(num)
            for i in range(num):
                if (i % 2 == 0) or (i % 3 == 0) or (i % 7 == 0):
                    _w[i] = 0
            self.w *= np.tile(_w, _index)

        self.delay = np.tile(np.arange(num), _index)*ms
        self.rate = 0


class ControlCircuit:
    def __init__(self, network):
        self.RS_L = Izhikevich('RS')
        self.RS_R = Izhikevich('RS')
        network.add([self.RS_L, self.RS_R])

class DecisionCircuit:
    def __init__(self, network, num=1):
        self.CH_L = Izhikevich('CH', num=num)
        self.CH_R = Izhikevich('CH', num=num)
        self.LTS_L = Izhikevich('LTS', num=num)
        self.LTS_R = Izhikevich('LTS', num=num)
        self.RS = Izhikevich('RS', num=num)
        network.add([self.CH_L, self.CH_R, self.LTS_L, self.LTS_R, self.RS])

        self.stdp1 = STDP(self.RS, self.CH_L, static=False, j='i')
        self.stdp2 = STDP(self.RS, self.CH_R, static=False, wrand=self.get_w(self.stdp1.w), j='i')
        self.stdp3 = STDP(self.CH_L, self.LTS_L, condition='j!=i', part=True)
        self.stdp4 = STDP(self.CH_R, self.LTS_R, condition='j!=i', part=True, wrand=self.get_w(self.stdp3.w))
        self.stdp5 = STDP(self.CH_L, self.LTS_R, part=True)
        self.stdp6 = STDP(self.CH_R, self.LTS_L, part=True, wrand=self.get_w(self.stdp5.w))
        wrand = '- rand() - 1'
        self.stdp7 = STDP(self.LTS_L, self.CH_L, wrand=wrand, j='i')
        self.stdp8 = STDP(self.LTS_R, self.CH_R, wrand=self.get_w(self.stdp7.w), j='i')
        network.add([self.stdp1, self.stdp2, self.stdp3, self.stdp4, self.stdp5, self.stdp6, self.stdp7, self.stdp8])

    def get_w(self, w):
        return w + 0.1 * np.random.rand(1, len(w))[0] - 0.1 * np.random.rand(1, len(w))[0]


'''
神经元产生决策的时间过长
多个输入神经元有输入时，不易产生决策
'''
class Cue:
    def __init__(self, num, network, input, output_left, output_right, stdp_list, index, rate):
        self.num = num #神经元数量
        self.network = network
        self.input = input
        self.stdp_list = stdp_list
        self.location = -300 #线索的初始坐标
        self.maximun = 1000 #机械臂最大偏移，右边为正
        self.minimun = -1000
        self.trace = np.zeros(0)
        self.trace = np.append(self.trace, 0)
        self.trace = np.append(self.trace, self.location)
        self.index = index
        self.rate = rate

        self.left = SpikeMonitor(output_left)
        self.right = SpikeMonitor(output_right)
        self.network.add(self.left)
        self.network.add(self.right)

    @property
    def save_dir(self):
        return 'save-{}'.format(self.index)

    #向左或向右移动若干距离，右移时为1，左移时为-1
    def move(self, side=1, length=100):
        before = self.location
        self.location += side * length
        if self.location > self.maximun:
            over = self.location - self.maximun
            self.location = self.maximun - over
        if self.location < self.minimun:
            over = self.minimun - self.location
            self.location = self.minimun + over
        after = self.location
        self.trace[0] += 1
        self.trace = np.append(self.trace, self.location)
        if before * after <= 0:
            return True
        else:
            return False

    #获取线索所在位置对应激活的输入神经元
    def sense(self):
        self.input.I_ext = 0
        step = (self.maximun - self.minimun) / self.num
        index = int((self.location - self.minimun) / step)
        if index < 0:
            index = 0
        if index > self.num - 1:
            index = self.num - 1
        self.input.I_ext[index] = 10

    def run(self, during=6000*ms, learning_rate=0):
        for stdp in self.stdp_list:
            stdp.rate = learning_rate

        left_spikes = self.left.num_spikes
        right_spikes = self.right.num_spikes
        self.network.run(during)

        left_spikes = self.left.num_spikes - left_spikes
        right_spikes = self.right.num_spikes - right_spikes
        print(list(self.input.I_ext), left_spikes, right_spikes)
        return left_spikes, right_spikes

    def reset(self):
        for izh in self.network:
            if isinstance(izh, Izhikevich):
                izh.reset()
        self.input.I_ext = 0
        self.network.run(1000*ms)

    #加入network的顺序不变，可以按顺序存储
    def save(self):
        if not os.path.exists(self.save_dir):
            os.mkdir(self.save_dir)
        stdp_list = [stdp for stdp in self.network if isinstance(stdp, STDP)]
        for num, stdp in enumerate(stdp_list):
            np.save('{}/stdp-{}.npy'.format(self.save_dir, num), stdp.w)
        np.save('{}/trace.npy'.format(self.save_dir), self.trace)

    def load(self):
        stdp_list = [stdp for stdp in self.network if isinstance(stdp, STDP)]
        for num, stdp in enumerate(stdp_list):
            stdp.w = np.load('{}/stdp-{}.npy'.format(self.save_dir, num))
        self.trace = np.load('{}/trace.npy'.format(self.save_dir))
        self.location = self.trace[-1]

    #机械臂进行移动
    #判断线索激活的神经元
    #进行6s的决策,确保神经元产生决策
    #判断是否给予奖励或者惩罚（修改训练速率）
    #进行2s的训练
    #机械臂移动
    def next(self):
        self.sense()
        print('make decision')
        for i in range(10):
            for izh in self.network:
                if not isinstance(izh, Izhikevich):
                    continue
                if izh.type[0] != 1:
                    continue
                izh.I_ext = '0.5*rand()'

            left_spikes, right_spikes = self.run(1000*ms)

            if left_spikes > 0 and right_spikes > 0 or left_spikes == 0 and right_spikes == 0:
                continue
            break
        else:
            print('can not make decision')
            self.reset()
            return

        print('start learn')
        side = -1 if left_spikes > right_spikes else 1
        rate = self.rate if self.move(side) else 0

        self.run(2000*ms, rate)
        #self.save()
        self.reset() #重置神经元状态


'''
t0 = np.linspace(-15, 15, 1000)
plt.plot(t0, np.exp(-t0**2/4.5**2)*(1.2*np.exp(-t0**2/0.8**2) - 0.2))
'''
def test(index=0, rate=0.00025):
    start_scope()

    network = Network()

    cc = ControlCircuit(network)
    dc = DecisionCircuit(network, num=2)

    stdp1 = STDP(dc.CH_L, cc.RS_L)
    stdp2 = STDP(dc.CH_R, cc.RS_R)
    network.add([stdp1, stdp2])

    n1 = SpikeMonitor(dc.CH_L)
    n2 = SpikeMonitor(dc.CH_R)
    n3 = SpikeMonitor(dc.LTS_L)
    n4 = SpikeMonitor(dc.LTS_R)
    n5 = SpikeMonitor(dc.RS)
    left = SpikeMonitor(cc.RS_L)
    right = SpikeMonitor(cc.RS_R)
    sm1= StateMonitor(dc.CH_L, ['v', 'total_I', 'g'], record=True)
    sm2= StateMonitor(dc.CH_R, ['v', 'total_I', 'g'], record=True)

    n = [n1, n2, n3, n4, n5, left, right, sm1, sm2]
    network.add(n)

    #return dc
    cue = Cue(2, network, dc.RS, cc.RS_L, cc.RS_R, [dc.stdp2, dc.stdp3], index, rate)
    if os.path.exists('save-{}/stdp-0.npy'.format(index)):
        cue.load()
    cue.save()
    print(cue.trace[0], cue.location)
    #for i in range(1000):
    #    cue.next()
    #    print(cue.trace[0], cue.location)
    #return

    #dc.RS.I_ext[0] = 10
    #network.run(500*ms, report='text')
    cue.next()
    #cue.next()

    plt.figure(figsize=(12, 2 * len(n)))

    plt.subplot(711)
    brian_plot(n1)
    plt.title('Left CH Neuron')

    plt.subplot(712)
    brian_plot(n2)
    plt.title('Right CH Neuron')

    plt.subplot(713)
    brian_plot(n3)
    plt.title('Left LTS Neuron')

    plt.subplot(714)
    brian_plot(n4)
    plt.title('Right LTS Neuron')

    '''
    plt.subplot(715)
    brian_plot(n5)
    plt.title('Input RS Neuron')

    plt.subplot(716)
    brian_plot(left)
    plt.title('Output Left Neuron')

    plt.subplot(717)
    brian_plot(right)
    plt.title('Output Right Neuron')
    #plot_raster(n1.i, n1.t)
    '''
    
    plt.subplot(715)
    plt.plot(sm1.t/ms, sm1.g[0], label='0')
    plt.plot(sm2.t/ms, sm2.g[0], label='1')
    plt.legend()
    plt.xlabel('t (ms)')

    plt.subplot(716)
    plt.plot(sm1.t/ms, sm1.total_I[0], label='0')
    plt.plot(sm2.t/ms, sm2.total_I[0], label='1')
    plt.legend()
    plt.xlabel('t (ms)')
    
    plt.subplot(717)
    plt.plot(sm1.t/ms, sm1.v[0], label='0')
    plt.plot(sm2.t/ms, sm2.v[0], label='1')
    plt.legend()
    plt.xlabel('t (ms)')

    plt.show()


defaultclock.dt = 500.*us
if __name__ == '__main__':
    test(index=2, rate=0.00025)

