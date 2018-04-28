
'''
暂时记录自己对生物神经网络的理解，不一定准确，有时间再实现
'''

'''
在某一时刻接收到动作电位后，计算该神经元该时刻电位，如果超出阈值，则触发一个动作电位
每隔一段时间，生成新的神经元
'''
class Zxon(object):
    def __init__(self):
        pass




'''
Hodgkin–Huxley
FitzHugh-Nagumo
Leaky integrate-and-fire
Nonlinear integrate-and-fire
SRM
SRMo
McCulloch-Pitts
'''
import math
import time
import numpy as np
import matplotlib.pyplot as plt

class Synaptic(object):
    '''
    neuron: 连接的神经元
    weight: 权重(-1, 1)
    active: 活跃度
    active_time: 最后激活时间
    '''
    def __init__(self, neuron=None):
        self.neuron = neuron
        self.weight = 0
        self.active = 0
        self.active_time = time.time()

class Neuron(object):
    '''
    synaptic_list: 连接下一层神经元的突触列表
    threshold: 触发动作电位的阈值
    potential: time时刻的电位
    time: 上一次接收到动作电位的时刻
    decay: 衰减函数，如lambda p, t: p - t if p > t else 0，通过衰减函数求得当前时间的电位
    '''
    def __init__(self):
        self.synaptic = []

    def synaptic_add(self):
        pass

    def synaptic_del(self):
        '''
        清理超出时间且活跃度低的突触
        如果没有活跃突触，清理该神经元
        '''
        pass


class HHSynaptic(Synaptic):
    pass


class HHNeuron(Neuron):
    '''
    Hodgkin–Huxley
    '''
    g = np.array([36, 120, 0.3])
    e = np.array([-12, 115, 10.613])
    x = np.array([0.31, 0.05, 0.58]) #n, m, h
    dt = 0.01
    
    def get_alpha(self, v):
        alpha = np.zeros(3)
        alpha[0] = (10 - v) / (100 * (math.exp((10 - v) / 10) - 1))
        alpha[1] = (25 - v) / (10 * (math.exp((25 - v) / 10) - 1))
        alpha[2] = 0.07 * math.exp(-v / 20)
        return alpha
    
    def get_beta(self, v):
        beta = np.zeros(3)
        beta[0] = 0.125 * math.exp(-v / 80)
        beta[1] = 4 * math.exp(-v / 18)
        beta[2] = 1 / (math.exp((30 - v) / 10) + 1)
        return beta
    
    def potential(self, v, i_ext=0):
        alpha = self.get_alpha(v)
        beta = self.get_beta(v)
        
        tau = 1 / (alpha + beta)
 
        self.x = (1 - self.dt / tau) * self.x + self.dt * alpha
        
        gnmh = np.zeros(3)
        gnmh[0] = self.g[0] * math.pow(self.x[0], 4)
        gnmh[1] = self.g[1] * math.pow(self.x[1], 3) * self.x[2]
        gnmh[2] = self.g[2]
        
        v += self.dt * (i_ext - sum(gnmh * (v - self.e)))
        return v

    def draw(self):
        v = 0
        x = np.arange(-20, 50, self.dt)
        y = []
        for i in x:
            i_ext = 2
            v = self.potential(v, i_ext)
            y.append(v)

        plt.plot(x, y)
        plt.xlabel('Time / ms')
        plt.ylabel('Voltage / mV')
        plt.show()


import warnings
warnings.filterwarnings('ignore')

#import brian2
from brian2 import *

def neuron_test():
    start_scope()
    
    N = 100
    tau = 10*ms
    v0_max = 3.
    duration = 100*ms
    sigma = 0.2
    #(unless refractory)表示在不应期内方程不生效
    #sigma*xi*tau**-0.5表示噪声，sigma越大表示噪声越大
    eqs = '''
    dv/dt = (v0-v)/tau + sigma*xi*tau**-0.5: 1 (unless refractory)
    v0 : 1
    '''
    
    #refractory=15*ms表示15ms内不触发spike
    G = NeuronGroup(N, eqs, threshold='v > 1', reset='v = 0', refractory=5*ms, method='euler')
    G.v0 = 'i*v0_max/(N-1)'
    M = SpikeMonitor(G)

    run(duration)

    #t/ms表示将t转换为ms
    #for t in spikemon.t:
    #    plt.axvline(t/ms, ls='--', c='C1', lw=3)
    plt.figure(figsize=(12,4))
    plt.subplot(121)
    plt.plot(M.t/ms, M.i, '.k')
    plt.xlabel('Time (ms)')
    plt.ylabel('Neuron index')
    plt.subplot(122)
    plt.plot(G.v0, M.count/duration)
    plt.xlabel('v0')
    plt.ylabel('Firing rate (sp/s)')

def synapse_test1():
    start_scope()
    
    eqs = '''
    dv/dt = (I - v)/tau : 1
    I : 1
    tau : second
    '''
    
    G = NeuronGroup(3, eqs, threshold='v > 1', reset='v = 0', method='exact')
    G.I = [2, 0, 0]
    G.tau = [10, 100, 100]*ms
    
    #on_pre='v_post += 0.2'表示接收到spike后，突触后电位增加0.2
    #S.delay表示接收到spike后，突触后电位在delay时间后改变
    S = Synapses(G, G, 'w : 1', on_pre='v_post += w')
    S.connect(i=0, j=[1, 2])
    S.w = 'j*0.2'
    S.delay = 'j*2*ms'
    
    M = StateMonitor(G, 'v', record=True)
    
    run(50*ms)
    
    plt.plot(M.t/ms, M.v[0], label='Neuron 0')
    plt.plot(M.t/ms, M.v[1], label='Neuron 1')
    plt.plot(M.t/ms, M.v[2], label='Neuron 2')
    plt.xlabel('Time (ms)')
    plt.ylabel('v')
    plt.legend();

def visualise_connetivity(S):
    Ns = len(S.source)
    Nt = len(S.target)
    plt.figure(figsize=(10, 4)) #设置图大小
    
    #神经元连接状态
    plt.subplot(121) #subplot(mnp)，m行，n列，第p个
    plt.plot(zeros(Ns), arange(Ns), 'ok', ms=10)
    plt.plot(ones(Nt), arange(Nt), 'ok', ms=10)
    for i, j in zip(S.i, S.j):
        plt.plot([0, 1], [i, j], '-k') #画线，从(0, i)到(1, j)，k表示黑色，-表示实线，--表示虚线
    plt.xticks([0, 1], ['Source', 'Target']) #x轴坐标显示为对应标识
    plt.ylabel('Neuron index')
    plt.xlim(-0.1, 1.1) #设置x轴显示范围
    plt.ylim(-1, max(Ns, Nt))
    
    #连接的神经元（突触）
    plt.subplot(122)
    plt.plot(S.i, S.j, 'ok')
    plt.xlim(-1, Ns)
    plt.ylim(-1, Nt)
    plt.xlabel('Source neuron index')
    plt.ylabel('Target neuron index')

def synapse_test2():
    start_scope()
    
    N = 10
    G = NeuronGroup(N, 'v : 1')
    S = Synapses(G, G)
    
    #默认用i, j表示连接的两个神经元
    #condition表示连接条件，符合条件的两个神经元才能连接
    #p表示连接概率，即两个神经元直接有多大概率连接
    #skip_if_invalid表示跳过无效的连接
    #S.connect(condition='abs(i - j) < 4 and i != j')
    #S.connect(j='k for k in range(i - 3, i + 4) if i != k', skip_if_invalid=True) #k可能超出范围
    S.connect(j='i')
    
    visualise_connetivity(S)

def synapse_test3():
    start_scope()
    
    N = 30
    neuron_spacing = 50*umetre
    width = N/4.0*neuron_spacing
    
    G = NeuronGroup(N, 'x :metre')
    G.x = 'i*neuron_spacing'
    
    S = Synapses(G, G, 'w : 1')
    S.connect(condition='i != j')
    #保证单位一致
    S.w = 'exp(-(x_pre - x_post)**2/(2*width**2))'
    
    plt.scatter(S.x_pre/um, S.x_post/um, S.w*20)
    plt.xlabel('Source neuron position (um)')
    plt.ylabel('Target neuron position (um)')

def synapse_test4():
    start_scope()
    
    taupre = taupost = 20*ms
    wmax = 0.01
    Apre = 0.01
    Apost = -Apre*taupre/taupost*1.05
    
    #event-driven，事件驱动，只在spike触发时计算
    #clock-driven，时间驱动，在每个时间片计算
    G = NeuronGroup(2, 'v : 1', threshold='t > (1 + i)*10*ms', refractory=100*ms)
    S = Synapses(G, G,
                 '''
                 w : 1
                 dapre/dt = -apre/taupre : 1 (clock-driven)
                 dapost/dt = -apost/taupost : 1 (clock-driven)
                 ''',
                 on_pre='''
                 v_post += 0.005
                 apre += Apre
                 w += apost
                 ''',
                 on_post='''
                 apost += Apost
                 w += apre
                 ''')
    S.connect(i=0, j=1)
    M = StateMonitor(S, ['w', 'apre', 'apost'], record=True)
    M1 = StateMonitor(G, ['v'], record=True)
    
    run(30*ms)
    
    plt.figure(figsize=(4, 8))
    plt.subplot(211)
    plt.plot(M.t/ms, M.apre[0], label='apre')
    plt.plot(M.t/ms, M.apost[0], label='apost')
    plt.legend()
    plt.subplot(212)
    plt.plot(M.t/ms, M.w[0], label='w')
    plt.plot(M1.t/ms, M1.v[1], label='v')
    plt.legend(loc='best')
    plt.xlabel('Time (ms)')

def synapse_test5():
    start_scope()
    taupre = taupost = 20*ms
    Apre = 0.01
    Apost = -Apre*taupre/taupost*0.5
    
    tmax = 50*ms
    N = 100
    # Presynaptic neurons G spike at times from 0 to tmax
    # Postsynaptic neurons G spike at times from tmax to 0
    # So difference in spike times will vary from -tmax to +tmax
    G = NeuronGroup(N, 'tspike:second', threshold='t>tspike', refractory=100*ms)
    H = NeuronGroup(N, 'tspike:second', threshold='t>tspike', refractory=100*ms)
    G.tspike = 'i*tmax/(N-1)'
    H.tspike = '(N-1-i)*tmax/(N-1)'
    S = Synapses(G, H,
                 '''
                 w : 1
                 dapre/dt = -apre/taupre : 1 (event-driven)
                 dapost/dt = -apost/taupost : 1 (event-driven)
                 ''',
                 on_pre='''
                 apre += Apre
                 w = w+apost
                 ''',
                 on_post='''
                 apost += Apost
                 w = w+apre
                 ''')
    S.connect(j='i')
    run(tmax+1*ms)
    plot((H.tspike-G.tspike)/ms, S.w)
    xlabel(r'$\Delta t$ (ms)')
    ylabel(r'$\Delta w$')
    axhline(0, ls='-', c='k');

if __name__ == '__main__':
    #hh = HHNeuron()
    #hh.draw()
    
    #neuron_test()
    
    synapse_test5()
