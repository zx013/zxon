from brian2 import *
import matplotlib.pyplot as plt

#set_device('cpp_standalone') #
#prefs.codegen.target = 'cython'
prefs.codegen.target = 'cython'

def show(M):
    plt.xlabel('Time (ms)')
    plt.ylabel('v')
    plt.show()

def test_01():
    start_scope()

    N = 1
    tau_v = 10*ms
    tau_active = 10*ms

    #not_refractory，在不应期时为0，不在不应期时为1
    eqs = '''dv/dt = (1 - v)/tau_v : 1 (unless refractory)
    dw/dt = (-w / tau_active)*int(not_refractory) : 1'''

    G = NeuronGroup(N, eqs, threshold='v > 0.6', reset='v = 0; w += 0.1', refractory=5*ms)
    M = StateMonitor(G, ['v', 'w'], record=0)

    run(100*ms)

    plt.plot(M.t/ms, M.w[0])
    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_02():
    start_scope()
    P = NeuronGroup(10, '')
    Q = NeuronGroup(10, '')
    S = Synapses(P, Q, '''w : 1''')
    S.connect(j='i if i % 2 == 0')
    #S.w[a:b, c:d, e:f]，表示选择前神经元在a:b之间，后神经元在c:d之间的连接，如果同一对神经元有多条连接，e:f表示e到f之间到这几条连接，语法同python的切片语法
    #S.w[cond]，表示选择符合条件cond的连接

def test_03():
    start_scope()

    P = PoissonGroup(1, 100*Hz)
    G = NeuronGroup(1, 'v : 1')
    S = Synapses(P, G, on_pre='v += 0.1')
    S.connect(j='i')

    M = StateMonitor(G, 'v', record=0)

    run(100*ms)

    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_04():
    start_scope()

    N = 1
    indices = array([0])
    times = array([1])*ms
    inp = SpikeGeneratorGroup(N, indices, times)
    G = NeuronGroup(N, 'v : 1')
    S = Synapses(inp, G, on_pre='v+=0.1')
    S.connect(j='i')

    M = StateMonitor(G, 'v', record=0)
    run(5*ms)

    #若设置值小于已运行的时间，再次运行时会立即触发一个spike，若大于运行的时间，在运行总时间达到该值时，才触发spike
    inp.set_spikes(indices, array([6])*ms)
    run(5*ms)

    #TimedArray(array, dt)设置时间列表，array中每个值都持续dt时间，直接调用返回具体值

    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_05():
    start_scope()

    G = NeuronGroup(1, '''dv/dt = (-v + I)/(10*ms) : 1
                    I : 1''')
    G.run_regularly('''change = int(rand() < 0.5)
                    I = change*(rand()*2) + (1 - change)*I''',
                    dt=10*ms)
    M = StateMonitor(G, 'v', record=0)

    run(100*ms)

    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_06():
    start_scope()

    G = NeuronGroup(1, 'dv/dt = -v/(10*ms) : 1')
    P = PoissonInput(G, 'v', 100, 100*Hz, weight=0.1)

    M = StateMonitor(G, 'v', record=0)

    run(100*ms)

    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_07():
    start_scope()

    G = NeuronGroup(1, '''dv/dt = (-v + active)/(10*ms) : 1
                    active : 1''')
    G.v = 100

    #按文档说明，active后面的下划线关闭了单元检查
    #从打印值来看，active始终打印True，active_则是正确的值
    @network_operation(dt=10*ms)
    def update_active():
        G.active_ = 0
        G.active_[0] = rand()*100

    M = StateMonitor(G, 'v', record=0)

    run(100*ms)

    plt.plot(M.t/ms, M.v[0])
    show(M)

def test_08():
    start_scope()

    G = NeuronGroup(1, 'dv/dt = (1 - v)/(10*ms) : 1', threshold='rand() < 100*Hz*dt', reset='v = 0')
    G.run_regularly('v += rand()', dt=2*ms)
    #record为True时记录G中所有的神经元，为数字（列表）时记录对应的神经元
    M = StateMonitor(G, 'v', record=0)
    #只在spike触发时记录v的值，即v跳变到0之前的值
    S = SpikeMonitor(G, variables=['v'])

    run(100*ms)

    plt.plot(M.t/ms, M.v[0])
    plt.plot(S.t/ms, S.v, '.')
    show(M)

def test_09():
    start_scope()

    G = NeuronGroup(3, 'dv/dt = (1 - v)/(10*ms) : 1', threshold='rand() < 100*Hz*dt', reset='v = 0')

    M = StateMonitor(G, 'v', record=True)
    P = PopulationRateMonitor(G)

    run(100*ms)

    #M.v.T表示M.v的转置
    #plt.plot(M.t/ms, M.v.T/mV)
    plt.plot(P.t/ms, P.rate/Hz)
    show(P)

def test_10():
    start_scope()

    G = NeuronGroup(10, 'dv/dt = (1 - v)/(10*ms) : 1', threshold='v > 0.6', reset='v = 0')
    S = Synapses(G, G, model='w : 1', on_pre='v += w')
    S.connect('i != j')
    M1 = SpikeMonitor(G, variables='v')
    #dt设置监控间隔，defaultclock.dt设置所有变量的默认时间间隔
    M2 = StateMonitor(G, 'v', record=True, dt=2*ms)

    net = Network(collect())

    net.run(50*ms)

    plt.plot(M1.t/ms, M1.v, '.')
    plt.plot(M2.t/ms, M2.v[0])
    show(M2)

#store('name')，存储当前状态，标签为'name'，restore('name')恢复，主要用于多次重复的实验，以及多次重复的测试。Network同样提供该接口。

if __name__ == '__main__':
    test_10()
