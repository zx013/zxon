#include "objects.h"
#include "code_objects/synapses_4_pre_initialise_queue.h"
void _run_synapses_4_pre_initialise_queue() {
	using namespace brian;
 	
 double*   _ptr_array_defaultclock_dt = _array_defaultclock_dt;


    double* real_delays = synapses_4_pre.delay.empty() ? 0 : &(synapses_4_pre.delay[0]);
    int32_t* sources = synapses_4_pre.sources.empty() ? 0 : &(synapses_4_pre.sources[0]);
    const unsigned int n_delays = synapses_4_pre.delay.size();
    const unsigned int n_synapses = synapses_4_pre.sources.size();
    synapses_4_pre.prepare(10,
                        10,
                        real_delays, n_delays, sources,
                        n_synapses,
                        _ptr_array_defaultclock_dt[0]);
}
