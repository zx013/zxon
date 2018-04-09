
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
    x = np.array([0.31, 0.05, 0.58])
    dt = 0.1
    def potential(self, v):
        alpha = np.zeros(3)
        alpha[0] = (10 - v) / (100 * (math.exp((10 - v) / 10) - 1))
        alpha[1] = (25 - v) / (10 * (math.exp((25 - v) / 10) - 1))
        alpha[2] = 0.07 * math.exp(-v / 20)
        
        beta = np.zeros(3)
        beta[0] = 0.125 * math.exp(-v / 80)
        beta[1] = 4 * math.exp(-v / 18)
        beta[2] = 1 / (math.exp((30 - v) / 10) + 1)
        
        tau = 1 / (alpha + beta)
 
        self.x = (1 - self.dt / tau) * self.x + self.dt * alpha
        
        gnmh = np.zeros(3)
        gnmh[0] = self.g[0] * math.pow(self.x[0], 4)
        gnmh[1] = self.g[1] * math.pow(self.x[1], 3) * self.x[2]
        gnmh[2] = self.g[2]
        
        I = gnmh * (v - self.e)
        
        v += self.dt * (0 - sum(I))
        return v

    def draw(self):
        v = 0
        x = np.arange(-20, 50, self.dt)
        y = []
        for i in x:
            v = self.potential(v)
            y.append(v)

        plt.plot(x, y)
        plt.xlabel('Time / ms')
        plt.ylabel('Voltage / mV')
        plt.show()

if __name__ == '__main__':
    hh = HHNeuron()
    hh.draw()
