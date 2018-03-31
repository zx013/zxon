
'''
暂时记录自己对生物神经网络的理解，不一定准确，有时间再实现
'''

'''
突触
neuron: 突触连接的神经元
trans: 上一级神经元到突触传输时间 
weight: 权重，介于（-1, 1)之间，决定上一级动作电位的影响
'''
class Synaptic(object):
	pass


'''
神经元
synaptic_list: 连接下一层神经元的突触列表
threshold: 触发动作电位的阈值
potential: time时刻的电位
time: 上一次接收到动作电位的时刻
decay: 衰减函数，如lambda p, t: p - t if p > t else 0，通过衰减函数求得当前时间的电位
'''
class Neuron(object):
	pass


'''
在某一时刻接收到动作电位后，计算该神经元该时刻电位，如果超出阈值，则触发一个动作电位
每隔一段时间，生成新的神经元
'''
class Zxon(object):
	def __init__(self):
		pass
