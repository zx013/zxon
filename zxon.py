
'''
��ʱ��¼�Լ����������������⣬��һ��׼ȷ����ʱ����ʵ��
'''

'''
ͻ��
neuron: ͻ�����ӵ���Ԫ
trans: ��һ����Ԫ��ͻ������ʱ�� 
weight: Ȩ�أ����ڣ�-1, 1)֮�䣬������һ��������λ��Ӱ��
'''
class Synaptic(object):
	pass


'''
��Ԫ
synaptic_list: ������һ����Ԫ��ͻ���б�
threshold: ����������λ����ֵ
potential: timeʱ�̵ĵ�λ
time: ��һ�ν��յ�������λ��ʱ��
decay: ˥����������lambda p, t: p - t if p > t else 0��ͨ��˥��������õ�ǰʱ��ĵ�λ
'''
class Neuron(object):
	pass


'''
��ĳһʱ�̽��յ�������λ�󣬼������Ԫ��ʱ�̵�λ�����������ֵ���򴥷�һ��������λ
ÿ��һ��ʱ�䣬�����µ���Ԫ
'''
class Zxon(object):
	def __init__(self):
		pass
