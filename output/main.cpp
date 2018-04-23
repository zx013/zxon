#include <stdlib.h>
#include "objects.h"
#include <ctime>
#include <time.h>

#include "run.h"
#include "brianlib/common_math.h"
#include "randomkit.h"

#include "code_objects/neurongroup_1_resetter_codeobject.h"
#include "code_objects/neurongroup_1_stateupdater_codeobject.h"
#include "code_objects/neurongroup_1_thresholder_codeobject.h"
#include "code_objects/neurongroup_2_resetter_codeobject.h"
#include "code_objects/neurongroup_2_stateupdater_codeobject.h"
#include "code_objects/neurongroup_2_thresholder_codeobject.h"
#include "code_objects/neurongroup_3_resetter_codeobject.h"
#include "code_objects/neurongroup_3_stateupdater_codeobject.h"
#include "code_objects/neurongroup_3_thresholder_codeobject.h"
#include "code_objects/neurongroup_4_resetter_codeobject.h"
#include "code_objects/neurongroup_4_stateupdater_codeobject.h"
#include "code_objects/neurongroup_4_thresholder_codeobject.h"
#include "code_objects/neurongroup_resetter_codeobject.h"
#include "code_objects/neurongroup_stateupdater_codeobject.h"
#include "code_objects/neurongroup_thresholder_codeobject.h"
#include "code_objects/spikemonitor_1_codeobject.h"
#include "code_objects/spikemonitor_2_codeobject.h"
#include "code_objects/spikemonitor_3_codeobject.h"
#include "code_objects/spikemonitor_4_codeobject.h"
#include "code_objects/spikemonitor_codeobject.h"
#include "code_objects/statemonitor_1_codeobject.h"
#include "code_objects/statemonitor_2_codeobject.h"
#include "code_objects/statemonitor_3_codeobject.h"
#include "code_objects/statemonitor_4_codeobject.h"
#include "code_objects/statemonitor_codeobject.h"
#include "code_objects/synapses_1_pre_codeobject.h"
#include "code_objects/synapses_1_pre_initialise_queue.h"
#include "code_objects/synapses_1_pre_push_spikes.h"
#include "code_objects/synapses_1_synapses_create_generator_codeobject.h"
#include "code_objects/synapses_2_pre_codeobject.h"
#include "code_objects/synapses_2_pre_initialise_queue.h"
#include "code_objects/synapses_2_pre_push_spikes.h"
#include "code_objects/synapses_2_synapses_create_generator_codeobject.h"
#include "code_objects/synapses_3_pre_codeobject.h"
#include "code_objects/synapses_3_pre_initialise_queue.h"
#include "code_objects/synapses_3_pre_push_spikes.h"
#include "code_objects/synapses_3_synapses_create_generator_codeobject.h"
#include "code_objects/synapses_4_pre_codeobject.h"
#include "code_objects/synapses_4_pre_initialise_queue.h"
#include "code_objects/synapses_4_pre_push_spikes.h"
#include "code_objects/synapses_4_synapses_create_generator_codeobject.h"
#include "code_objects/synapses_pre_codeobject.h"
#include "code_objects/synapses_pre_initialise_queue.h"
#include "code_objects/synapses_pre_push_spikes.h"
#include "code_objects/synapses_synapses_create_generator_codeobject.h"


#include <iostream>
#include <fstream>




int main(int argc, char **argv)
{

	brian_start();

	{
		using namespace brian;

		
                
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _run_synapses_synapses_create_generator_codeobject();
        _array_statemonitor_clock_dt[0] = 0.002;
        _array_statemonitor_clock_dt[0] = 0.002;
        
                        
                        for(int i=0; i<_num__array_statemonitor__indices; i++)
                        {
                            _array_statemonitor__indices[i] = _static_array__array_statemonitor__indices[i];
                        }
                        
        _array_statemonitor_clock_timestep[0] = 0;
        _array_statemonitor_clock_t[0] = 0.0;
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _run_synapses_pre_initialise_queue();
        network.clear();
        network.add(&statemonitor_clock, _run_statemonitor_codeobject);
        network.add(&defaultclock, _run_neurongroup_stateupdater_codeobject);
        network.add(&defaultclock, _run_neurongroup_thresholder_codeobject);
        network.add(&defaultclock, _run_spikemonitor_codeobject);
        network.add(&defaultclock, _run_synapses_pre_push_spikes);
        network.add(&defaultclock, _run_synapses_pre_codeobject);
        network.add(&defaultclock, _run_neurongroup_resetter_codeobject);
        network.run(0.05, NULL, 10.0);
        _run_synapses_1_synapses_create_generator_codeobject();
        _array_statemonitor_1_clock_dt[0] = 0.002;
        _array_statemonitor_1_clock_dt[0] = 0.002;
        
                        
                        for(int i=0; i<_num__array_statemonitor_1__indices; i++)
                        {
                            _array_statemonitor_1__indices[i] = _static_array__array_statemonitor_1__indices[i];
                        }
                        
        _array_statemonitor_1_clock_timestep[0] = 0;
        _array_statemonitor_1_clock_t[0] = 0.0;
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _run_synapses_1_pre_initialise_queue();
        network_1.clear();
        network_1.add(&statemonitor_1_clock, _run_statemonitor_1_codeobject);
        network_1.add(&defaultclock, _run_neurongroup_1_stateupdater_codeobject);
        network_1.add(&defaultclock, _run_neurongroup_1_thresholder_codeobject);
        network_1.add(&defaultclock, _run_spikemonitor_1_codeobject);
        network_1.add(&defaultclock, _run_synapses_1_pre_push_spikes);
        network_1.add(&defaultclock, _run_synapses_1_pre_codeobject);
        network_1.add(&defaultclock, _run_neurongroup_1_resetter_codeobject);
        network_1.run(0.05, NULL, 10.0);
        _run_synapses_2_synapses_create_generator_codeobject();
        _array_statemonitor_2_clock_dt[0] = 0.002;
        _array_statemonitor_2_clock_dt[0] = 0.002;
        
                        
                        for(int i=0; i<_num__array_statemonitor_2__indices; i++)
                        {
                            _array_statemonitor_2__indices[i] = _static_array__array_statemonitor_2__indices[i];
                        }
                        
        _array_statemonitor_2_clock_timestep[0] = 0;
        _array_statemonitor_2_clock_t[0] = 0.0;
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _run_synapses_2_pre_initialise_queue();
        network_2.clear();
        network_2.add(&statemonitor_2_clock, _run_statemonitor_2_codeobject);
        network_2.add(&defaultclock, _run_neurongroup_2_stateupdater_codeobject);
        network_2.add(&defaultclock, _run_neurongroup_2_thresholder_codeobject);
        network_2.add(&defaultclock, _run_spikemonitor_2_codeobject);
        network_2.add(&defaultclock, _run_synapses_2_pre_push_spikes);
        network_2.add(&defaultclock, _run_synapses_2_pre_codeobject);
        network_2.add(&defaultclock, _run_neurongroup_2_resetter_codeobject);
        network_2.run(0.05, NULL, 10.0);
        _run_synapses_3_synapses_create_generator_codeobject();
        _array_statemonitor_3_clock_dt[0] = 0.002;
        _array_statemonitor_3_clock_dt[0] = 0.002;
        
                        
                        for(int i=0; i<_num__array_statemonitor_3__indices; i++)
                        {
                            _array_statemonitor_3__indices[i] = _static_array__array_statemonitor_3__indices[i];
                        }
                        
        _array_statemonitor_3_clock_timestep[0] = 0;
        _array_statemonitor_3_clock_t[0] = 0.0;
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _run_synapses_3_pre_initialise_queue();
        network_3.clear();
        network_3.add(&statemonitor_3_clock, _run_statemonitor_3_codeobject);
        network_3.add(&defaultclock, _run_neurongroup_3_stateupdater_codeobject);
        network_3.add(&defaultclock, _run_neurongroup_3_thresholder_codeobject);
        network_3.add(&defaultclock, _run_spikemonitor_3_codeobject);
        network_3.add(&defaultclock, _run_synapses_3_pre_push_spikes);
        network_3.add(&defaultclock, _run_synapses_3_pre_codeobject);
        network_3.add(&defaultclock, _run_neurongroup_3_resetter_codeobject);
        network_3.run(0.05, NULL, 10.0);
        _run_synapses_4_synapses_create_generator_codeobject();
        _array_statemonitor_4_clock_dt[0] = 0.002;
        _array_statemonitor_4_clock_dt[0] = 0.002;
        
                        
                        for(int i=0; i<_num__array_statemonitor_4__indices; i++)
                        {
                            _array_statemonitor_4__indices[i] = _static_array__array_statemonitor_4__indices[i];
                        }
                        
        _array_statemonitor_4_clock_timestep[0] = 0;
        _array_statemonitor_4_clock_t[0] = 0.0;
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _run_synapses_4_pre_initialise_queue();
        network_4.clear();
        network_4.add(&statemonitor_4_clock, _run_statemonitor_4_codeobject);
        network_4.add(&defaultclock, _run_neurongroup_4_stateupdater_codeobject);
        network_4.add(&defaultclock, _run_neurongroup_4_thresholder_codeobject);
        network_4.add(&defaultclock, _run_spikemonitor_4_codeobject);
        network_4.add(&defaultclock, _run_synapses_4_pre_push_spikes);
        network_4.add(&defaultclock, _run_synapses_4_pre_codeobject);
        network_4.add(&defaultclock, _run_neurongroup_4_resetter_codeobject);
        network_4.run(0.05, NULL, 10.0);
        #ifdef DEBUG
        _debugmsg_spikemonitor_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_1_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_1_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_2_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_2_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_3_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_3_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_4_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_4_pre_codeobject();
        #endif

	}

	brian_end();

	return 0;
}