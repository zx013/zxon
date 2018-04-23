#include<stdlib.h>
#include "objects.h"
#include<ctime>
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


void brian_start()
{
	_init_arrays();
	_load_arrays();
	// Initialize clocks (link timestep and dt to the respective arrays)
    brian::defaultclock.timestep = brian::_array_defaultclock_timestep;
    brian::defaultclock.dt = brian::_array_defaultclock_dt;
    brian::defaultclock.t = brian::_array_defaultclock_t;
    brian::statemonitor_1_clock.timestep = brian::_array_statemonitor_1_clock_timestep;
    brian::statemonitor_1_clock.dt = brian::_array_statemonitor_1_clock_dt;
    brian::statemonitor_1_clock.t = brian::_array_statemonitor_1_clock_t;
    brian::statemonitor_2_clock.timestep = brian::_array_statemonitor_2_clock_timestep;
    brian::statemonitor_2_clock.dt = brian::_array_statemonitor_2_clock_dt;
    brian::statemonitor_2_clock.t = brian::_array_statemonitor_2_clock_t;
    brian::statemonitor_3_clock.timestep = brian::_array_statemonitor_3_clock_timestep;
    brian::statemonitor_3_clock.dt = brian::_array_statemonitor_3_clock_dt;
    brian::statemonitor_3_clock.t = brian::_array_statemonitor_3_clock_t;
    brian::statemonitor_4_clock.timestep = brian::_array_statemonitor_4_clock_timestep;
    brian::statemonitor_4_clock.dt = brian::_array_statemonitor_4_clock_dt;
    brian::statemonitor_4_clock.t = brian::_array_statemonitor_4_clock_t;
    brian::statemonitor_clock.timestep = brian::_array_statemonitor_clock_timestep;
    brian::statemonitor_clock.dt = brian::_array_statemonitor_clock_dt;
    brian::statemonitor_clock.t = brian::_array_statemonitor_clock_t;
    for (int i=0; i<1; i++)
	    rk_randomseed(brian::_mersenne_twister_states[i]);  // Note that this seed can be potentially replaced in main.cpp
}

void brian_end()
{
	_write_arrays();
	_dealloc_arrays();
}


