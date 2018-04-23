
#include "objects.h"
#include "synapses_classes.h"
#include "brianlib/clocks.h"
#include "brianlib/dynamic_array.h"
#include "brianlib/stdint_compat.h"
#include "network.h"
#include "randomkit.h"
#include<vector>
#include<iostream>
#include<fstream>

namespace brian {

std::vector< rk_state* > _mersenne_twister_states;

//////////////// networks /////////////////
Network magicnetwork;
Network network;
Network network_1;
Network network_2;
Network network_3;
Network network_4;

//////////////// arrays ///////////////////
double * _array_defaultclock_dt;
const int _num__array_defaultclock_dt = 1;
double * _array_defaultclock_t;
const int _num__array_defaultclock_t = 1;
int64_t * _array_defaultclock_timestep;
const int _num__array_defaultclock_timestep = 1;
int32_t * _array_neurongroup_1__spikespace;
const int _num__array_neurongroup_1__spikespace = 11;
int32_t * _array_neurongroup_1_i;
const int _num__array_neurongroup_1_i = 10;
double * _array_neurongroup_1_v;
const int _num__array_neurongroup_1_v = 10;
int32_t * _array_neurongroup_2__spikespace;
const int _num__array_neurongroup_2__spikespace = 11;
int32_t * _array_neurongroup_2_i;
const int _num__array_neurongroup_2_i = 10;
double * _array_neurongroup_2_v;
const int _num__array_neurongroup_2_v = 10;
int32_t * _array_neurongroup_3__spikespace;
const int _num__array_neurongroup_3__spikespace = 11;
int32_t * _array_neurongroup_3_i;
const int _num__array_neurongroup_3_i = 10;
double * _array_neurongroup_3_v;
const int _num__array_neurongroup_3_v = 10;
int32_t * _array_neurongroup_4__spikespace;
const int _num__array_neurongroup_4__spikespace = 11;
int32_t * _array_neurongroup_4_i;
const int _num__array_neurongroup_4_i = 10;
double * _array_neurongroup_4_v;
const int _num__array_neurongroup_4_v = 10;
int32_t * _array_neurongroup__spikespace;
const int _num__array_neurongroup__spikespace = 11;
int32_t * _array_neurongroup_i;
const int _num__array_neurongroup_i = 10;
double * _array_neurongroup_v;
const int _num__array_neurongroup_v = 10;
int32_t * _array_spikemonitor_1__source_idx;
const int _num__array_spikemonitor_1__source_idx = 10;
int32_t * _array_spikemonitor_1_count;
const int _num__array_spikemonitor_1_count = 10;
int32_t * _array_spikemonitor_1_N;
const int _num__array_spikemonitor_1_N = 1;
int32_t * _array_spikemonitor_2__source_idx;
const int _num__array_spikemonitor_2__source_idx = 10;
int32_t * _array_spikemonitor_2_count;
const int _num__array_spikemonitor_2_count = 10;
int32_t * _array_spikemonitor_2_N;
const int _num__array_spikemonitor_2_N = 1;
int32_t * _array_spikemonitor_3__source_idx;
const int _num__array_spikemonitor_3__source_idx = 10;
int32_t * _array_spikemonitor_3_count;
const int _num__array_spikemonitor_3_count = 10;
int32_t * _array_spikemonitor_3_N;
const int _num__array_spikemonitor_3_N = 1;
int32_t * _array_spikemonitor_4__source_idx;
const int _num__array_spikemonitor_4__source_idx = 10;
int32_t * _array_spikemonitor_4_count;
const int _num__array_spikemonitor_4_count = 10;
int32_t * _array_spikemonitor_4_N;
const int _num__array_spikemonitor_4_N = 1;
int32_t * _array_spikemonitor__source_idx;
const int _num__array_spikemonitor__source_idx = 10;
int32_t * _array_spikemonitor_count;
const int _num__array_spikemonitor_count = 10;
int32_t * _array_spikemonitor_N;
const int _num__array_spikemonitor_N = 1;
int32_t * _array_statemonitor_1__indices;
const int _num__array_statemonitor_1__indices = 10;
double * _array_statemonitor_1_clock_dt;
const int _num__array_statemonitor_1_clock_dt = 1;
double * _array_statemonitor_1_clock_t;
const int _num__array_statemonitor_1_clock_t = 1;
int64_t * _array_statemonitor_1_clock_timestep;
const int _num__array_statemonitor_1_clock_timestep = 1;
int32_t * _array_statemonitor_1_N;
const int _num__array_statemonitor_1_N = 1;
double * _array_statemonitor_1_v;
const int _num__array_statemonitor_1_v = (0, 10);
int32_t * _array_statemonitor_2__indices;
const int _num__array_statemonitor_2__indices = 10;
double * _array_statemonitor_2_clock_dt;
const int _num__array_statemonitor_2_clock_dt = 1;
double * _array_statemonitor_2_clock_t;
const int _num__array_statemonitor_2_clock_t = 1;
int64_t * _array_statemonitor_2_clock_timestep;
const int _num__array_statemonitor_2_clock_timestep = 1;
int32_t * _array_statemonitor_2_N;
const int _num__array_statemonitor_2_N = 1;
double * _array_statemonitor_2_v;
const int _num__array_statemonitor_2_v = (0, 10);
int32_t * _array_statemonitor_3__indices;
const int _num__array_statemonitor_3__indices = 10;
double * _array_statemonitor_3_clock_dt;
const int _num__array_statemonitor_3_clock_dt = 1;
double * _array_statemonitor_3_clock_t;
const int _num__array_statemonitor_3_clock_t = 1;
int64_t * _array_statemonitor_3_clock_timestep;
const int _num__array_statemonitor_3_clock_timestep = 1;
int32_t * _array_statemonitor_3_N;
const int _num__array_statemonitor_3_N = 1;
double * _array_statemonitor_3_v;
const int _num__array_statemonitor_3_v = (0, 10);
int32_t * _array_statemonitor_4__indices;
const int _num__array_statemonitor_4__indices = 10;
double * _array_statemonitor_4_clock_dt;
const int _num__array_statemonitor_4_clock_dt = 1;
double * _array_statemonitor_4_clock_t;
const int _num__array_statemonitor_4_clock_t = 1;
int64_t * _array_statemonitor_4_clock_timestep;
const int _num__array_statemonitor_4_clock_timestep = 1;
int32_t * _array_statemonitor_4_N;
const int _num__array_statemonitor_4_N = 1;
double * _array_statemonitor_4_v;
const int _num__array_statemonitor_4_v = (0, 10);
int32_t * _array_statemonitor__indices;
const int _num__array_statemonitor__indices = 10;
double * _array_statemonitor_clock_dt;
const int _num__array_statemonitor_clock_dt = 1;
double * _array_statemonitor_clock_t;
const int _num__array_statemonitor_clock_t = 1;
int64_t * _array_statemonitor_clock_timestep;
const int _num__array_statemonitor_clock_timestep = 1;
int32_t * _array_statemonitor_N;
const int _num__array_statemonitor_N = 1;
double * _array_statemonitor_v;
const int _num__array_statemonitor_v = (0, 10);
int32_t * _array_synapses_1_N;
const int _num__array_synapses_1_N = 1;
int32_t * _array_synapses_2_N;
const int _num__array_synapses_2_N = 1;
int32_t * _array_synapses_3_N;
const int _num__array_synapses_3_N = 1;
int32_t * _array_synapses_4_N;
const int _num__array_synapses_4_N = 1;
int32_t * _array_synapses_N;
const int _num__array_synapses_N = 1;

//////////////// dynamic arrays 1d /////////
std::vector<int32_t> _dynamic_array_spikemonitor_1_i;
std::vector<double> _dynamic_array_spikemonitor_1_t;
std::vector<double> _dynamic_array_spikemonitor_1_v;
std::vector<int32_t> _dynamic_array_spikemonitor_2_i;
std::vector<double> _dynamic_array_spikemonitor_2_t;
std::vector<double> _dynamic_array_spikemonitor_2_v;
std::vector<int32_t> _dynamic_array_spikemonitor_3_i;
std::vector<double> _dynamic_array_spikemonitor_3_t;
std::vector<double> _dynamic_array_spikemonitor_3_v;
std::vector<int32_t> _dynamic_array_spikemonitor_4_i;
std::vector<double> _dynamic_array_spikemonitor_4_t;
std::vector<double> _dynamic_array_spikemonitor_4_v;
std::vector<int32_t> _dynamic_array_spikemonitor_i;
std::vector<double> _dynamic_array_spikemonitor_t;
std::vector<double> _dynamic_array_spikemonitor_v;
std::vector<double> _dynamic_array_statemonitor_1_t;
std::vector<double> _dynamic_array_statemonitor_2_t;
std::vector<double> _dynamic_array_statemonitor_3_t;
std::vector<double> _dynamic_array_statemonitor_4_t;
std::vector<double> _dynamic_array_statemonitor_t;
std::vector<int32_t> _dynamic_array_synapses_1__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_1__synaptic_pre;
std::vector<double> _dynamic_array_synapses_1_delay;
std::vector<double> _dynamic_array_synapses_1_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_1_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_1_N_outgoing;
std::vector<double> _dynamic_array_synapses_1_w;
std::vector<int32_t> _dynamic_array_synapses_2__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_2__synaptic_pre;
std::vector<double> _dynamic_array_synapses_2_delay;
std::vector<double> _dynamic_array_synapses_2_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_2_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_2_N_outgoing;
std::vector<double> _dynamic_array_synapses_2_w;
std::vector<int32_t> _dynamic_array_synapses_3__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_3__synaptic_pre;
std::vector<double> _dynamic_array_synapses_3_delay;
std::vector<double> _dynamic_array_synapses_3_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_3_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_3_N_outgoing;
std::vector<double> _dynamic_array_synapses_3_w;
std::vector<int32_t> _dynamic_array_synapses_4__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_4__synaptic_pre;
std::vector<double> _dynamic_array_synapses_4_delay;
std::vector<double> _dynamic_array_synapses_4_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_4_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_4_N_outgoing;
std::vector<double> _dynamic_array_synapses_4_w;
std::vector<int32_t> _dynamic_array_synapses__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses__synaptic_pre;
std::vector<double> _dynamic_array_synapses_delay;
std::vector<double> _dynamic_array_synapses_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_N_outgoing;
std::vector<double> _dynamic_array_synapses_w;

//////////////// dynamic arrays 2d /////////
DynamicArray2D<double> _dynamic_array_statemonitor_1_v;
DynamicArray2D<double> _dynamic_array_statemonitor_2_v;
DynamicArray2D<double> _dynamic_array_statemonitor_3_v;
DynamicArray2D<double> _dynamic_array_statemonitor_4_v;
DynamicArray2D<double> _dynamic_array_statemonitor_v;

/////////////// static arrays /////////////
int32_t * _static_array__array_statemonitor_1__indices;
const int _num__static_array__array_statemonitor_1__indices = 10;
int32_t * _static_array__array_statemonitor_2__indices;
const int _num__static_array__array_statemonitor_2__indices = 10;
int32_t * _static_array__array_statemonitor_3__indices;
const int _num__static_array__array_statemonitor_3__indices = 10;
int32_t * _static_array__array_statemonitor_4__indices;
const int _num__static_array__array_statemonitor_4__indices = 10;
int32_t * _static_array__array_statemonitor__indices;
const int _num__static_array__array_statemonitor__indices = 10;

//////////////// synapses /////////////////
// synapses
SynapticPathway<double> synapses_pre(
		_dynamic_array_synapses_delay,
		_dynamic_array_synapses__synaptic_pre,
		0, 10);
// synapses_1
SynapticPathway<double> synapses_1_pre(
		_dynamic_array_synapses_1_delay,
		_dynamic_array_synapses_1__synaptic_pre,
		0, 10);
// synapses_2
SynapticPathway<double> synapses_2_pre(
		_dynamic_array_synapses_2_delay,
		_dynamic_array_synapses_2__synaptic_pre,
		0, 10);
// synapses_3
SynapticPathway<double> synapses_3_pre(
		_dynamic_array_synapses_3_delay,
		_dynamic_array_synapses_3__synaptic_pre,
		0, 10);
// synapses_4
SynapticPathway<double> synapses_4_pre(
		_dynamic_array_synapses_4_delay,
		_dynamic_array_synapses_4__synaptic_pre,
		0, 10);

//////////////// clocks ///////////////////
Clock defaultclock;  // attributes will be set in run.cpp
Clock statemonitor_1_clock;  // attributes will be set in run.cpp
Clock statemonitor_2_clock;  // attributes will be set in run.cpp
Clock statemonitor_3_clock;  // attributes will be set in run.cpp
Clock statemonitor_4_clock;  // attributes will be set in run.cpp
Clock statemonitor_clock;  // attributes will be set in run.cpp

// Profiling information for each code object
double neurongroup_1_resetter_codeobject_profiling_info = 0.0;
double neurongroup_1_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_1_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_2_resetter_codeobject_profiling_info = 0.0;
double neurongroup_2_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_2_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_3_resetter_codeobject_profiling_info = 0.0;
double neurongroup_3_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_3_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_4_resetter_codeobject_profiling_info = 0.0;
double neurongroup_4_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_4_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_resetter_codeobject_profiling_info = 0.0;
double neurongroup_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_thresholder_codeobject_profiling_info = 0.0;
double spikemonitor_1_codeobject_profiling_info = 0.0;
double spikemonitor_2_codeobject_profiling_info = 0.0;
double spikemonitor_3_codeobject_profiling_info = 0.0;
double spikemonitor_4_codeobject_profiling_info = 0.0;
double spikemonitor_codeobject_profiling_info = 0.0;
double statemonitor_1_codeobject_profiling_info = 0.0;
double statemonitor_2_codeobject_profiling_info = 0.0;
double statemonitor_3_codeobject_profiling_info = 0.0;
double statemonitor_4_codeobject_profiling_info = 0.0;
double statemonitor_codeobject_profiling_info = 0.0;
double synapses_1_pre_codeobject_profiling_info = 0.0;
double synapses_1_pre_initialise_queue_profiling_info = 0.0;
double synapses_1_pre_push_spikes_profiling_info = 0.0;
double synapses_1_synapses_create_generator_codeobject_profiling_info = 0.0;
double synapses_2_pre_codeobject_profiling_info = 0.0;
double synapses_2_pre_initialise_queue_profiling_info = 0.0;
double synapses_2_pre_push_spikes_profiling_info = 0.0;
double synapses_2_synapses_create_generator_codeobject_profiling_info = 0.0;
double synapses_3_pre_codeobject_profiling_info = 0.0;
double synapses_3_pre_initialise_queue_profiling_info = 0.0;
double synapses_3_pre_push_spikes_profiling_info = 0.0;
double synapses_3_synapses_create_generator_codeobject_profiling_info = 0.0;
double synapses_4_pre_codeobject_profiling_info = 0.0;
double synapses_4_pre_initialise_queue_profiling_info = 0.0;
double synapses_4_pre_push_spikes_profiling_info = 0.0;
double synapses_4_synapses_create_generator_codeobject_profiling_info = 0.0;
double synapses_pre_codeobject_profiling_info = 0.0;
double synapses_pre_initialise_queue_profiling_info = 0.0;
double synapses_pre_push_spikes_profiling_info = 0.0;
double synapses_synapses_create_generator_codeobject_profiling_info = 0.0;

}

void _init_arrays()
{
	using namespace brian;

    // Arrays initialized to 0
	_array_defaultclock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_dt[i] = 0;

	_array_defaultclock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_t[i] = 0;

	_array_defaultclock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_timestep[i] = 0;

	_array_neurongroup_1__spikespace = new int32_t[11];
    
	for(int i=0; i<11; i++) _array_neurongroup_1__spikespace[i] = 0;

	_array_neurongroup_1_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_1_i[i] = 0;

	_array_neurongroup_1_v = new double[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_1_v[i] = 0;

	_array_neurongroup_2__spikespace = new int32_t[11];
    
	for(int i=0; i<11; i++) _array_neurongroup_2__spikespace[i] = 0;

	_array_neurongroup_2_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_2_i[i] = 0;

	_array_neurongroup_2_v = new double[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_2_v[i] = 0;

	_array_neurongroup_3__spikespace = new int32_t[11];
    
	for(int i=0; i<11; i++) _array_neurongroup_3__spikespace[i] = 0;

	_array_neurongroup_3_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_3_i[i] = 0;

	_array_neurongroup_3_v = new double[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_3_v[i] = 0;

	_array_neurongroup_4__spikespace = new int32_t[11];
    
	for(int i=0; i<11; i++) _array_neurongroup_4__spikespace[i] = 0;

	_array_neurongroup_4_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_4_i[i] = 0;

	_array_neurongroup_4_v = new double[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_4_v[i] = 0;

	_array_neurongroup__spikespace = new int32_t[11];
    
	for(int i=0; i<11; i++) _array_neurongroup__spikespace[i] = 0;

	_array_neurongroup_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_i[i] = 0;

	_array_neurongroup_v = new double[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_v[i] = 0;

	_array_spikemonitor_1__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_1__source_idx[i] = 0;

	_array_spikemonitor_1_count = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_1_count[i] = 0;

	_array_spikemonitor_1_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_1_N[i] = 0;

	_array_spikemonitor_2__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_2__source_idx[i] = 0;

	_array_spikemonitor_2_count = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_2_count[i] = 0;

	_array_spikemonitor_2_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_2_N[i] = 0;

	_array_spikemonitor_3__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_3__source_idx[i] = 0;

	_array_spikemonitor_3_count = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_3_count[i] = 0;

	_array_spikemonitor_3_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_3_N[i] = 0;

	_array_spikemonitor_4__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_4__source_idx[i] = 0;

	_array_spikemonitor_4_count = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_4_count[i] = 0;

	_array_spikemonitor_4_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_4_N[i] = 0;

	_array_spikemonitor__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor__source_idx[i] = 0;

	_array_spikemonitor_count = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_count[i] = 0;

	_array_spikemonitor_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_N[i] = 0;

	_array_statemonitor_1__indices = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_statemonitor_1__indices[i] = 0;

	_array_statemonitor_1_clock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_1_clock_dt[i] = 0;

	_array_statemonitor_1_clock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_1_clock_t[i] = 0;

	_array_statemonitor_1_clock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_1_clock_timestep[i] = 0;

	_array_statemonitor_1_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_1_N[i] = 0;

	_array_statemonitor_2__indices = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_statemonitor_2__indices[i] = 0;

	_array_statemonitor_2_clock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_2_clock_dt[i] = 0;

	_array_statemonitor_2_clock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_2_clock_t[i] = 0;

	_array_statemonitor_2_clock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_2_clock_timestep[i] = 0;

	_array_statemonitor_2_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_2_N[i] = 0;

	_array_statemonitor_3__indices = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_statemonitor_3__indices[i] = 0;

	_array_statemonitor_3_clock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_3_clock_dt[i] = 0;

	_array_statemonitor_3_clock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_3_clock_t[i] = 0;

	_array_statemonitor_3_clock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_3_clock_timestep[i] = 0;

	_array_statemonitor_3_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_3_N[i] = 0;

	_array_statemonitor_4__indices = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_statemonitor_4__indices[i] = 0;

	_array_statemonitor_4_clock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_4_clock_dt[i] = 0;

	_array_statemonitor_4_clock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_4_clock_t[i] = 0;

	_array_statemonitor_4_clock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_4_clock_timestep[i] = 0;

	_array_statemonitor_4_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_4_N[i] = 0;

	_array_statemonitor__indices = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_statemonitor__indices[i] = 0;

	_array_statemonitor_clock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_clock_dt[i] = 0;

	_array_statemonitor_clock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_clock_t[i] = 0;

	_array_statemonitor_clock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_clock_timestep[i] = 0;

	_array_statemonitor_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_statemonitor_N[i] = 0;

	_array_synapses_1_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_1_N[i] = 0;

	_array_synapses_2_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_2_N[i] = 0;

	_array_synapses_3_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_3_N[i] = 0;

	_array_synapses_4_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_4_N[i] = 0;

	_array_synapses_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_N[i] = 0;


	// Arrays initialized to an "arange"
	_array_neurongroup_1_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_1_i[i] = 0 + i;

	_array_neurongroup_2_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_2_i[i] = 0 + i;

	_array_neurongroup_3_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_3_i[i] = 0 + i;

	_array_neurongroup_4_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_4_i[i] = 0 + i;

	_array_neurongroup_i = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_neurongroup_i[i] = 0 + i;

	_array_spikemonitor_1__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_1__source_idx[i] = 0 + i;

	_array_spikemonitor_2__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_2__source_idx[i] = 0 + i;

	_array_spikemonitor_3__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_3__source_idx[i] = 0 + i;

	_array_spikemonitor_4__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor_4__source_idx[i] = 0 + i;

	_array_spikemonitor__source_idx = new int32_t[10];
    
	for(int i=0; i<10; i++) _array_spikemonitor__source_idx[i] = 0 + i;


	// static arrays
	_static_array__array_statemonitor_1__indices = new int32_t[10];
	_static_array__array_statemonitor_2__indices = new int32_t[10];
	_static_array__array_statemonitor_3__indices = new int32_t[10];
	_static_array__array_statemonitor_4__indices = new int32_t[10];
	_static_array__array_statemonitor__indices = new int32_t[10];

	// Random number generator states
	for (int i=0; i<1; i++)
	    _mersenne_twister_states.push_back(new rk_state());
}

void _load_arrays()
{
	using namespace brian;

	ifstream f_static_array__array_statemonitor_1__indices;
	f_static_array__array_statemonitor_1__indices.open("static_arrays/_static_array__array_statemonitor_1__indices", ios::in | ios::binary);
	if(f_static_array__array_statemonitor_1__indices.is_open())
	{
		f_static_array__array_statemonitor_1__indices.read(reinterpret_cast<char*>(_static_array__array_statemonitor_1__indices), 10*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_statemonitor_1__indices." << endl;
	}
	ifstream f_static_array__array_statemonitor_2__indices;
	f_static_array__array_statemonitor_2__indices.open("static_arrays/_static_array__array_statemonitor_2__indices", ios::in | ios::binary);
	if(f_static_array__array_statemonitor_2__indices.is_open())
	{
		f_static_array__array_statemonitor_2__indices.read(reinterpret_cast<char*>(_static_array__array_statemonitor_2__indices), 10*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_statemonitor_2__indices." << endl;
	}
	ifstream f_static_array__array_statemonitor_3__indices;
	f_static_array__array_statemonitor_3__indices.open("static_arrays/_static_array__array_statemonitor_3__indices", ios::in | ios::binary);
	if(f_static_array__array_statemonitor_3__indices.is_open())
	{
		f_static_array__array_statemonitor_3__indices.read(reinterpret_cast<char*>(_static_array__array_statemonitor_3__indices), 10*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_statemonitor_3__indices." << endl;
	}
	ifstream f_static_array__array_statemonitor_4__indices;
	f_static_array__array_statemonitor_4__indices.open("static_arrays/_static_array__array_statemonitor_4__indices", ios::in | ios::binary);
	if(f_static_array__array_statemonitor_4__indices.is_open())
	{
		f_static_array__array_statemonitor_4__indices.read(reinterpret_cast<char*>(_static_array__array_statemonitor_4__indices), 10*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_statemonitor_4__indices." << endl;
	}
	ifstream f_static_array__array_statemonitor__indices;
	f_static_array__array_statemonitor__indices.open("static_arrays/_static_array__array_statemonitor__indices", ios::in | ios::binary);
	if(f_static_array__array_statemonitor__indices.is_open())
	{
		f_static_array__array_statemonitor__indices.read(reinterpret_cast<char*>(_static_array__array_statemonitor__indices), 10*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_statemonitor__indices." << endl;
	}
}

void _write_arrays()
{
	using namespace brian;

	ofstream outfile__array_defaultclock_dt;
	outfile__array_defaultclock_dt.open("results\\_array_defaultclock_dt_-8986205317229209898", ios::binary | ios::out);
	if(outfile__array_defaultclock_dt.is_open())
	{
		outfile__array_defaultclock_dt.write(reinterpret_cast<char*>(_array_defaultclock_dt), 1*sizeof(_array_defaultclock_dt[0]));
		outfile__array_defaultclock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_dt." << endl;
	}
	ofstream outfile__array_defaultclock_t;
	outfile__array_defaultclock_t.open("results\\_array_defaultclock_t_-1547939415464234186", ios::binary | ios::out);
	if(outfile__array_defaultclock_t.is_open())
	{
		outfile__array_defaultclock_t.write(reinterpret_cast<char*>(_array_defaultclock_t), 1*sizeof(_array_defaultclock_t[0]));
		outfile__array_defaultclock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_t." << endl;
	}
	ofstream outfile__array_defaultclock_timestep;
	outfile__array_defaultclock_timestep.open("results\\_array_defaultclock_timestep_1640722804348145880", ios::binary | ios::out);
	if(outfile__array_defaultclock_timestep.is_open())
	{
		outfile__array_defaultclock_timestep.write(reinterpret_cast<char*>(_array_defaultclock_timestep), 1*sizeof(_array_defaultclock_timestep[0]));
		outfile__array_defaultclock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_timestep." << endl;
	}
	ofstream outfile__array_neurongroup_1__spikespace;
	outfile__array_neurongroup_1__spikespace.open("results\\_array_neurongroup_1__spikespace_1773453016006317080", ios::binary | ios::out);
	if(outfile__array_neurongroup_1__spikespace.is_open())
	{
		outfile__array_neurongroup_1__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_1__spikespace), 11*sizeof(_array_neurongroup_1__spikespace[0]));
		outfile__array_neurongroup_1__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_1_i;
	outfile__array_neurongroup_1_i.open("results\\_array_neurongroup_1_i_-5986479282297187141", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_i.is_open())
	{
		outfile__array_neurongroup_1_i.write(reinterpret_cast<char*>(_array_neurongroup_1_i), 10*sizeof(_array_neurongroup_1_i[0]));
		outfile__array_neurongroup_1_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_i." << endl;
	}
	ofstream outfile__array_neurongroup_1_v;
	outfile__array_neurongroup_1_v.open("results\\_array_neurongroup_1_v_-2638704753901545187", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_v.is_open())
	{
		outfile__array_neurongroup_1_v.write(reinterpret_cast<char*>(_array_neurongroup_1_v), 10*sizeof(_array_neurongroup_1_v[0]));
		outfile__array_neurongroup_1_v.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_v." << endl;
	}
	ofstream outfile__array_neurongroup_2__spikespace;
	outfile__array_neurongroup_2__spikespace.open("results\\_array_neurongroup_2__spikespace_-9032172157695265883", ios::binary | ios::out);
	if(outfile__array_neurongroup_2__spikespace.is_open())
	{
		outfile__array_neurongroup_2__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_2__spikespace), 11*sizeof(_array_neurongroup_2__spikespace[0]));
		outfile__array_neurongroup_2__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_2_i;
	outfile__array_neurongroup_2_i.open("results\\_array_neurongroup_2_i_117161505438330722", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_i.is_open())
	{
		outfile__array_neurongroup_2_i.write(reinterpret_cast<char*>(_array_neurongroup_2_i), 10*sizeof(_array_neurongroup_2_i[0]));
		outfile__array_neurongroup_2_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_i." << endl;
	}
	ofstream outfile__array_neurongroup_2_v;
	outfile__array_neurongroup_2_v.open("results\\_array_neurongroup_2_v_1581682154960930245", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_v.is_open())
	{
		outfile__array_neurongroup_2_v.write(reinterpret_cast<char*>(_array_neurongroup_2_v), 10*sizeof(_array_neurongroup_2_v[0]));
		outfile__array_neurongroup_2_v.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_v." << endl;
	}
	ofstream outfile__array_neurongroup_3__spikespace;
	outfile__array_neurongroup_3__spikespace.open("results\\_array_neurongroup_3__spikespace_3936249332237503822", ios::binary | ios::out);
	if(outfile__array_neurongroup_3__spikespace.is_open())
	{
		outfile__array_neurongroup_3__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_3__spikespace), 11*sizeof(_array_neurongroup_3__spikespace[0]));
		outfile__array_neurongroup_3__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_3_i;
	outfile__array_neurongroup_3_i.open("results\\_array_neurongroup_3_i_-6856501599390357948", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_i.is_open())
	{
		outfile__array_neurongroup_3_i.write(reinterpret_cast<char*>(_array_neurongroup_3_i), 10*sizeof(_array_neurongroup_3_i[0]));
		outfile__array_neurongroup_3_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_i." << endl;
	}
	ofstream outfile__array_neurongroup_3_v;
	outfile__array_neurongroup_3_v.open("results\\_array_neurongroup_3_v_3314994663096954460", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_v.is_open())
	{
		outfile__array_neurongroup_3_v.write(reinterpret_cast<char*>(_array_neurongroup_3_v), 10*sizeof(_array_neurongroup_3_v[0]));
		outfile__array_neurongroup_3_v.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_v." << endl;
	}
	ofstream outfile__array_neurongroup_4__spikespace;
	outfile__array_neurongroup_4__spikespace.open("results\\_array_neurongroup_4__spikespace_2488151110197744733", ios::binary | ios::out);
	if(outfile__array_neurongroup_4__spikespace.is_open())
	{
		outfile__array_neurongroup_4__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_4__spikespace), 11*sizeof(_array_neurongroup_4__spikespace[0]));
		outfile__array_neurongroup_4__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_4_i;
	outfile__array_neurongroup_4_i.open("results\\_array_neurongroup_4_i_-4359590316782307891", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_i.is_open())
	{
		outfile__array_neurongroup_4_i.write(reinterpret_cast<char*>(_array_neurongroup_4_i), 10*sizeof(_array_neurongroup_4_i[0]));
		outfile__array_neurongroup_4_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_i." << endl;
	}
	ofstream outfile__array_neurongroup_4_v;
	outfile__array_neurongroup_4_v.open("results\\_array_neurongroup_4_v_4552279489579140645", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_v.is_open())
	{
		outfile__array_neurongroup_4_v.write(reinterpret_cast<char*>(_array_neurongroup_4_v), 10*sizeof(_array_neurongroup_4_v[0]));
		outfile__array_neurongroup_4_v.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_v." << endl;
	}
	ofstream outfile__array_neurongroup__spikespace;
	outfile__array_neurongroup__spikespace.open("results\\_array_neurongroup__spikespace_-3055838356342413890", ios::binary | ios::out);
	if(outfile__array_neurongroup__spikespace.is_open())
	{
		outfile__array_neurongroup__spikespace.write(reinterpret_cast<char*>(_array_neurongroup__spikespace), 11*sizeof(_array_neurongroup__spikespace[0]));
		outfile__array_neurongroup__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_i;
	outfile__array_neurongroup_i.open("results\\_array_neurongroup_i_-4019963975581421313", ios::binary | ios::out);
	if(outfile__array_neurongroup_i.is_open())
	{
		outfile__array_neurongroup_i.write(reinterpret_cast<char*>(_array_neurongroup_i), 10*sizeof(_array_neurongroup_i[0]));
		outfile__array_neurongroup_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_i." << endl;
	}
	ofstream outfile__array_neurongroup_v;
	outfile__array_neurongroup_v.open("results\\_array_neurongroup_v_1570438913288238384", ios::binary | ios::out);
	if(outfile__array_neurongroup_v.is_open())
	{
		outfile__array_neurongroup_v.write(reinterpret_cast<char*>(_array_neurongroup_v), 10*sizeof(_array_neurongroup_v[0]));
		outfile__array_neurongroup_v.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_v." << endl;
	}
	ofstream outfile__array_spikemonitor_1__source_idx;
	outfile__array_spikemonitor_1__source_idx.open("results\\_array_spikemonitor_1__source_idx_-8295509049015550925", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1__source_idx.is_open())
	{
		outfile__array_spikemonitor_1__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_1__source_idx), 10*sizeof(_array_spikemonitor_1__source_idx[0]));
		outfile__array_spikemonitor_1__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_1_count;
	outfile__array_spikemonitor_1_count.open("results\\_array_spikemonitor_1_count_-4852453769560484478", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_count.is_open())
	{
		outfile__array_spikemonitor_1_count.write(reinterpret_cast<char*>(_array_spikemonitor_1_count), 10*sizeof(_array_spikemonitor_1_count[0]));
		outfile__array_spikemonitor_1_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_count." << endl;
	}
	ofstream outfile__array_spikemonitor_1_N;
	outfile__array_spikemonitor_1_N.open("results\\_array_spikemonitor_1_N_2474453427986529941", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_N.is_open())
	{
		outfile__array_spikemonitor_1_N.write(reinterpret_cast<char*>(_array_spikemonitor_1_N), 1*sizeof(_array_spikemonitor_1_N[0]));
		outfile__array_spikemonitor_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_N." << endl;
	}
	ofstream outfile__array_spikemonitor_2__source_idx;
	outfile__array_spikemonitor_2__source_idx.open("results\\_array_spikemonitor_2__source_idx_-6604425973710822266", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2__source_idx.is_open())
	{
		outfile__array_spikemonitor_2__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_2__source_idx), 10*sizeof(_array_spikemonitor_2__source_idx[0]));
		outfile__array_spikemonitor_2__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_2_count;
	outfile__array_spikemonitor_2_count.open("results\\_array_spikemonitor_2_count_-2609435453270709890", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_count.is_open())
	{
		outfile__array_spikemonitor_2_count.write(reinterpret_cast<char*>(_array_spikemonitor_2_count), 10*sizeof(_array_spikemonitor_2_count[0]));
		outfile__array_spikemonitor_2_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_count." << endl;
	}
	ofstream outfile__array_spikemonitor_2_N;
	outfile__array_spikemonitor_2_N.open("results\\_array_spikemonitor_2_N_7293768390035435860", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_N.is_open())
	{
		outfile__array_spikemonitor_2_N.write(reinterpret_cast<char*>(_array_spikemonitor_2_N), 1*sizeof(_array_spikemonitor_2_N[0]));
		outfile__array_spikemonitor_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_N." << endl;
	}
	ofstream outfile__array_spikemonitor_3__source_idx;
	outfile__array_spikemonitor_3__source_idx.open("results\\_array_spikemonitor_3__source_idx_665131884167565319", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3__source_idx.is_open())
	{
		outfile__array_spikemonitor_3__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_3__source_idx), 10*sizeof(_array_spikemonitor_3__source_idx[0]));
		outfile__array_spikemonitor_3__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_3_count;
	outfile__array_spikemonitor_3_count.open("results\\_array_spikemonitor_3_count_2959999151051594404", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_count.is_open())
	{
		outfile__array_spikemonitor_3_count.write(reinterpret_cast<char*>(_array_spikemonitor_3_count), 10*sizeof(_array_spikemonitor_3_count[0]));
		outfile__array_spikemonitor_3_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_count." << endl;
	}
	ofstream outfile__array_spikemonitor_3_N;
	outfile__array_spikemonitor_3_N.open("results\\_array_spikemonitor_3_N_5453658158483651029", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_N.is_open())
	{
		outfile__array_spikemonitor_3_N.write(reinterpret_cast<char*>(_array_spikemonitor_3_N), 1*sizeof(_array_spikemonitor_3_N[0]));
		outfile__array_spikemonitor_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_N." << endl;
	}
	ofstream outfile__array_spikemonitor_4__source_idx;
	outfile__array_spikemonitor_4__source_idx.open("results\\_array_spikemonitor_4__source_idx_2607845141582312465", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4__source_idx.is_open())
	{
		outfile__array_spikemonitor_4__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_4__source_idx), 10*sizeof(_array_spikemonitor_4__source_idx[0]));
		outfile__array_spikemonitor_4__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_4_count;
	outfile__array_spikemonitor_4_count.open("results\\_array_spikemonitor_4_count_3456150089478248000", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_count.is_open())
	{
		outfile__array_spikemonitor_4_count.write(reinterpret_cast<char*>(_array_spikemonitor_4_count), 10*sizeof(_array_spikemonitor_4_count[0]));
		outfile__array_spikemonitor_4_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_count." << endl;
	}
	ofstream outfile__array_spikemonitor_4_N;
	outfile__array_spikemonitor_4_N.open("results\\_array_spikemonitor_4_N_7717405418571191830", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_N.is_open())
	{
		outfile__array_spikemonitor_4_N.write(reinterpret_cast<char*>(_array_spikemonitor_4_N), 1*sizeof(_array_spikemonitor_4_N[0]));
		outfile__array_spikemonitor_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_N." << endl;
	}
	ofstream outfile__array_spikemonitor__source_idx;
	outfile__array_spikemonitor__source_idx.open("results\\_array_spikemonitor__source_idx_7491765110299602101", ios::binary | ios::out);
	if(outfile__array_spikemonitor__source_idx.is_open())
	{
		outfile__array_spikemonitor__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor__source_idx), 10*sizeof(_array_spikemonitor__source_idx[0]));
		outfile__array_spikemonitor__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_count;
	outfile__array_spikemonitor_count.open("results\\_array_spikemonitor_count_3287202690683731643", ios::binary | ios::out);
	if(outfile__array_spikemonitor_count.is_open())
	{
		outfile__array_spikemonitor_count.write(reinterpret_cast<char*>(_array_spikemonitor_count), 10*sizeof(_array_spikemonitor_count[0]));
		outfile__array_spikemonitor_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_count." << endl;
	}
	ofstream outfile__array_spikemonitor_N;
	outfile__array_spikemonitor_N.open("results\\_array_spikemonitor_N_-4753288715534272449", ios::binary | ios::out);
	if(outfile__array_spikemonitor_N.is_open())
	{
		outfile__array_spikemonitor_N.write(reinterpret_cast<char*>(_array_spikemonitor_N), 1*sizeof(_array_spikemonitor_N[0]));
		outfile__array_spikemonitor_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_N." << endl;
	}
	ofstream outfile__array_statemonitor_1__indices;
	outfile__array_statemonitor_1__indices.open("results\\_array_statemonitor_1__indices_8681491466397425762", ios::binary | ios::out);
	if(outfile__array_statemonitor_1__indices.is_open())
	{
		outfile__array_statemonitor_1__indices.write(reinterpret_cast<char*>(_array_statemonitor_1__indices), 10*sizeof(_array_statemonitor_1__indices[0]));
		outfile__array_statemonitor_1__indices.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_1__indices." << endl;
	}
	ofstream outfile__array_statemonitor_1_clock_dt;
	outfile__array_statemonitor_1_clock_dt.open("results\\_array_statemonitor_1_clock_dt_2354220109132919060", ios::binary | ios::out);
	if(outfile__array_statemonitor_1_clock_dt.is_open())
	{
		outfile__array_statemonitor_1_clock_dt.write(reinterpret_cast<char*>(_array_statemonitor_1_clock_dt), 1*sizeof(_array_statemonitor_1_clock_dt[0]));
		outfile__array_statemonitor_1_clock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_1_clock_dt." << endl;
	}
	ofstream outfile__array_statemonitor_1_clock_t;
	outfile__array_statemonitor_1_clock_t.open("results\\_array_statemonitor_1_clock_t_552072317714192083", ios::binary | ios::out);
	if(outfile__array_statemonitor_1_clock_t.is_open())
	{
		outfile__array_statemonitor_1_clock_t.write(reinterpret_cast<char*>(_array_statemonitor_1_clock_t), 1*sizeof(_array_statemonitor_1_clock_t[0]));
		outfile__array_statemonitor_1_clock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_1_clock_t." << endl;
	}
	ofstream outfile__array_statemonitor_1_clock_timestep;
	outfile__array_statemonitor_1_clock_timestep.open("results\\_array_statemonitor_1_clock_timestep_-104754665710234750", ios::binary | ios::out);
	if(outfile__array_statemonitor_1_clock_timestep.is_open())
	{
		outfile__array_statemonitor_1_clock_timestep.write(reinterpret_cast<char*>(_array_statemonitor_1_clock_timestep), 1*sizeof(_array_statemonitor_1_clock_timestep[0]));
		outfile__array_statemonitor_1_clock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_1_clock_timestep." << endl;
	}
	ofstream outfile__array_statemonitor_1_N;
	outfile__array_statemonitor_1_N.open("results\\_array_statemonitor_1_N_-7660143577483774994", ios::binary | ios::out);
	if(outfile__array_statemonitor_1_N.is_open())
	{
		outfile__array_statemonitor_1_N.write(reinterpret_cast<char*>(_array_statemonitor_1_N), 1*sizeof(_array_statemonitor_1_N[0]));
		outfile__array_statemonitor_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_1_N." << endl;
	}
	ofstream outfile__array_statemonitor_2__indices;
	outfile__array_statemonitor_2__indices.open("results\\_array_statemonitor_2__indices_-3702528352380413682", ios::binary | ios::out);
	if(outfile__array_statemonitor_2__indices.is_open())
	{
		outfile__array_statemonitor_2__indices.write(reinterpret_cast<char*>(_array_statemonitor_2__indices), 10*sizeof(_array_statemonitor_2__indices[0]));
		outfile__array_statemonitor_2__indices.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_2__indices." << endl;
	}
	ofstream outfile__array_statemonitor_2_clock_dt;
	outfile__array_statemonitor_2_clock_dt.open("results\\_array_statemonitor_2_clock_dt_-4110580432003985364", ios::binary | ios::out);
	if(outfile__array_statemonitor_2_clock_dt.is_open())
	{
		outfile__array_statemonitor_2_clock_dt.write(reinterpret_cast<char*>(_array_statemonitor_2_clock_dt), 1*sizeof(_array_statemonitor_2_clock_dt[0]));
		outfile__array_statemonitor_2_clock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_2_clock_dt." << endl;
	}
	ofstream outfile__array_statemonitor_2_clock_t;
	outfile__array_statemonitor_2_clock_t.open("results\\_array_statemonitor_2_clock_t_4115075066280989218", ios::binary | ios::out);
	if(outfile__array_statemonitor_2_clock_t.is_open())
	{
		outfile__array_statemonitor_2_clock_t.write(reinterpret_cast<char*>(_array_statemonitor_2_clock_t), 1*sizeof(_array_statemonitor_2_clock_t[0]));
		outfile__array_statemonitor_2_clock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_2_clock_t." << endl;
	}
	ofstream outfile__array_statemonitor_2_clock_timestep;
	outfile__array_statemonitor_2_clock_timestep.open("results\\_array_statemonitor_2_clock_timestep_-4891674089740653996", ios::binary | ios::out);
	if(outfile__array_statemonitor_2_clock_timestep.is_open())
	{
		outfile__array_statemonitor_2_clock_timestep.write(reinterpret_cast<char*>(_array_statemonitor_2_clock_timestep), 1*sizeof(_array_statemonitor_2_clock_timestep[0]));
		outfile__array_statemonitor_2_clock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_2_clock_timestep." << endl;
	}
	ofstream outfile__array_statemonitor_2_N;
	outfile__array_statemonitor_2_N.open("results\\_array_statemonitor_2_N_-5068688515345726875", ios::binary | ios::out);
	if(outfile__array_statemonitor_2_N.is_open())
	{
		outfile__array_statemonitor_2_N.write(reinterpret_cast<char*>(_array_statemonitor_2_N), 1*sizeof(_array_statemonitor_2_N[0]));
		outfile__array_statemonitor_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_2_N." << endl;
	}
	ofstream outfile__array_statemonitor_3__indices;
	outfile__array_statemonitor_3__indices.open("results\\_array_statemonitor_3__indices_-7606571585687629966", ios::binary | ios::out);
	if(outfile__array_statemonitor_3__indices.is_open())
	{
		outfile__array_statemonitor_3__indices.write(reinterpret_cast<char*>(_array_statemonitor_3__indices), 10*sizeof(_array_statemonitor_3__indices[0]));
		outfile__array_statemonitor_3__indices.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_3__indices." << endl;
	}
	ofstream outfile__array_statemonitor_3_clock_dt;
	outfile__array_statemonitor_3_clock_dt.open("results\\_array_statemonitor_3_clock_dt_2696904705063377670", ios::binary | ios::out);
	if(outfile__array_statemonitor_3_clock_dt.is_open())
	{
		outfile__array_statemonitor_3_clock_dt.write(reinterpret_cast<char*>(_array_statemonitor_3_clock_dt), 1*sizeof(_array_statemonitor_3_clock_dt[0]));
		outfile__array_statemonitor_3_clock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_3_clock_dt." << endl;
	}
	ofstream outfile__array_statemonitor_3_clock_t;
	outfile__array_statemonitor_3_clock_t.open("results\\_array_statemonitor_3_clock_t_-882212823153018681", ios::binary | ios::out);
	if(outfile__array_statemonitor_3_clock_t.is_open())
	{
		outfile__array_statemonitor_3_clock_t.write(reinterpret_cast<char*>(_array_statemonitor_3_clock_t), 1*sizeof(_array_statemonitor_3_clock_t[0]));
		outfile__array_statemonitor_3_clock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_3_clock_t." << endl;
	}
	ofstream outfile__array_statemonitor_3_clock_timestep;
	outfile__array_statemonitor_3_clock_timestep.open("results\\_array_statemonitor_3_clock_timestep_5474301353267725663", ios::binary | ios::out);
	if(outfile__array_statemonitor_3_clock_timestep.is_open())
	{
		outfile__array_statemonitor_3_clock_timestep.write(reinterpret_cast<char*>(_array_statemonitor_3_clock_timestep), 1*sizeof(_array_statemonitor_3_clock_timestep[0]));
		outfile__array_statemonitor_3_clock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_3_clock_timestep." << endl;
	}
	ofstream outfile__array_statemonitor_3_N;
	outfile__array_statemonitor_3_N.open("results\\_array_statemonitor_3_N_990088828079949059", ios::binary | ios::out);
	if(outfile__array_statemonitor_3_N.is_open())
	{
		outfile__array_statemonitor_3_N.write(reinterpret_cast<char*>(_array_statemonitor_3_N), 1*sizeof(_array_statemonitor_3_N[0]));
		outfile__array_statemonitor_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_3_N." << endl;
	}
	ofstream outfile__array_statemonitor_4__indices;
	outfile__array_statemonitor_4__indices.open("results\\_array_statemonitor_4__indices_5095382784565296197", ios::binary | ios::out);
	if(outfile__array_statemonitor_4__indices.is_open())
	{
		outfile__array_statemonitor_4__indices.write(reinterpret_cast<char*>(_array_statemonitor_4__indices), 10*sizeof(_array_statemonitor_4__indices[0]));
		outfile__array_statemonitor_4__indices.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_4__indices." << endl;
	}
	ofstream outfile__array_statemonitor_4_clock_dt;
	outfile__array_statemonitor_4_clock_dt.open("results\\_array_statemonitor_4_clock_dt_-3676021109364138829", ios::binary | ios::out);
	if(outfile__array_statemonitor_4_clock_dt.is_open())
	{
		outfile__array_statemonitor_4_clock_dt.write(reinterpret_cast<char*>(_array_statemonitor_4_clock_dt), 1*sizeof(_array_statemonitor_4_clock_dt[0]));
		outfile__array_statemonitor_4_clock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_4_clock_dt." << endl;
	}
	ofstream outfile__array_statemonitor_4_clock_t;
	outfile__array_statemonitor_4_clock_t.open("results\\_array_statemonitor_4_clock_t_-8167739699810296568", ios::binary | ios::out);
	if(outfile__array_statemonitor_4_clock_t.is_open())
	{
		outfile__array_statemonitor_4_clock_t.write(reinterpret_cast<char*>(_array_statemonitor_4_clock_t), 1*sizeof(_array_statemonitor_4_clock_t[0]));
		outfile__array_statemonitor_4_clock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_4_clock_t." << endl;
	}
	ofstream outfile__array_statemonitor_4_clock_timestep;
	outfile__array_statemonitor_4_clock_timestep.open("results\\_array_statemonitor_4_clock_timestep_-6382963653713979454", ios::binary | ios::out);
	if(outfile__array_statemonitor_4_clock_timestep.is_open())
	{
		outfile__array_statemonitor_4_clock_timestep.write(reinterpret_cast<char*>(_array_statemonitor_4_clock_timestep), 1*sizeof(_array_statemonitor_4_clock_timestep[0]));
		outfile__array_statemonitor_4_clock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_4_clock_timestep." << endl;
	}
	ofstream outfile__array_statemonitor_4_N;
	outfile__array_statemonitor_4_N.open("results\\_array_statemonitor_4_N_6556795730643683347", ios::binary | ios::out);
	if(outfile__array_statemonitor_4_N.is_open())
	{
		outfile__array_statemonitor_4_N.write(reinterpret_cast<char*>(_array_statemonitor_4_N), 1*sizeof(_array_statemonitor_4_N[0]));
		outfile__array_statemonitor_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_4_N." << endl;
	}
	ofstream outfile__array_statemonitor__indices;
	outfile__array_statemonitor__indices.open("results\\_array_statemonitor__indices_2220679672970870264", ios::binary | ios::out);
	if(outfile__array_statemonitor__indices.is_open())
	{
		outfile__array_statemonitor__indices.write(reinterpret_cast<char*>(_array_statemonitor__indices), 10*sizeof(_array_statemonitor__indices[0]));
		outfile__array_statemonitor__indices.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor__indices." << endl;
	}
	ofstream outfile__array_statemonitor_clock_dt;
	outfile__array_statemonitor_clock_dt.open("results\\_array_statemonitor_clock_dt_-3514764890982316441", ios::binary | ios::out);
	if(outfile__array_statemonitor_clock_dt.is_open())
	{
		outfile__array_statemonitor_clock_dt.write(reinterpret_cast<char*>(_array_statemonitor_clock_dt), 1*sizeof(_array_statemonitor_clock_dt[0]));
		outfile__array_statemonitor_clock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_clock_dt." << endl;
	}
	ofstream outfile__array_statemonitor_clock_t;
	outfile__array_statemonitor_clock_t.open("results\\_array_statemonitor_clock_t_-1566587743469759634", ios::binary | ios::out);
	if(outfile__array_statemonitor_clock_t.is_open())
	{
		outfile__array_statemonitor_clock_t.write(reinterpret_cast<char*>(_array_statemonitor_clock_t), 1*sizeof(_array_statemonitor_clock_t[0]));
		outfile__array_statemonitor_clock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_clock_t." << endl;
	}
	ofstream outfile__array_statemonitor_clock_timestep;
	outfile__array_statemonitor_clock_timestep.open("results\\_array_statemonitor_clock_timestep_5319749898130385188", ios::binary | ios::out);
	if(outfile__array_statemonitor_clock_timestep.is_open())
	{
		outfile__array_statemonitor_clock_timestep.write(reinterpret_cast<char*>(_array_statemonitor_clock_timestep), 1*sizeof(_array_statemonitor_clock_timestep[0]));
		outfile__array_statemonitor_clock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_clock_timestep." << endl;
	}
	ofstream outfile__array_statemonitor_N;
	outfile__array_statemonitor_N.open("results\\_array_statemonitor_N_-1788534305110346101", ios::binary | ios::out);
	if(outfile__array_statemonitor_N.is_open())
	{
		outfile__array_statemonitor_N.write(reinterpret_cast<char*>(_array_statemonitor_N), 1*sizeof(_array_statemonitor_N[0]));
		outfile__array_statemonitor_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_statemonitor_N." << endl;
	}
	ofstream outfile__array_synapses_1_N;
	outfile__array_synapses_1_N.open("results\\_array_synapses_1_N_6361417444871883783", ios::binary | ios::out);
	if(outfile__array_synapses_1_N.is_open())
	{
		outfile__array_synapses_1_N.write(reinterpret_cast<char*>(_array_synapses_1_N), 1*sizeof(_array_synapses_1_N[0]));
		outfile__array_synapses_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_N." << endl;
	}
	ofstream outfile__array_synapses_2_N;
	outfile__array_synapses_2_N.open("results\\_array_synapses_2_N_-8276617773384609455", ios::binary | ios::out);
	if(outfile__array_synapses_2_N.is_open())
	{
		outfile__array_synapses_2_N.write(reinterpret_cast<char*>(_array_synapses_2_N), 1*sizeof(_array_synapses_2_N[0]));
		outfile__array_synapses_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_N." << endl;
	}
	ofstream outfile__array_synapses_3_N;
	outfile__array_synapses_3_N.open("results\\_array_synapses_3_N_-7184527718945517901", ios::binary | ios::out);
	if(outfile__array_synapses_3_N.is_open())
	{
		outfile__array_synapses_3_N.write(reinterpret_cast<char*>(_array_synapses_3_N), 1*sizeof(_array_synapses_3_N[0]));
		outfile__array_synapses_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_N." << endl;
	}
	ofstream outfile__array_synapses_4_N;
	outfile__array_synapses_4_N.open("results\\_array_synapses_4_N_7946922585010529659", ios::binary | ios::out);
	if(outfile__array_synapses_4_N.is_open())
	{
		outfile__array_synapses_4_N.write(reinterpret_cast<char*>(_array_synapses_4_N), 1*sizeof(_array_synapses_4_N[0]));
		outfile__array_synapses_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_N." << endl;
	}
	ofstream outfile__array_synapses_N;
	outfile__array_synapses_N.open("results\\_array_synapses_N_7063885288914902446", ios::binary | ios::out);
	if(outfile__array_synapses_N.is_open())
	{
		outfile__array_synapses_N.write(reinterpret_cast<char*>(_array_synapses_N), 1*sizeof(_array_synapses_N[0]));
		outfile__array_synapses_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_N." << endl;
	}

	ofstream outfile__dynamic_array_spikemonitor_1_i;
	outfile__dynamic_array_spikemonitor_1_i.open("results\\_dynamic_array_spikemonitor_1_i_8732210991621331668", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_1_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_1_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_1_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_1_i[0]), _dynamic_array_spikemonitor_1_i.size()*sizeof(_dynamic_array_spikemonitor_1_i[0]));
		    outfile__dynamic_array_spikemonitor_1_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_1_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_1_t;
	outfile__dynamic_array_spikemonitor_1_t.open("results\\_dynamic_array_spikemonitor_1_t_5326875259237062868", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_1_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_1_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_1_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_1_t[0]), _dynamic_array_spikemonitor_1_t.size()*sizeof(_dynamic_array_spikemonitor_1_t[0]));
		    outfile__dynamic_array_spikemonitor_1_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_1_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_1_v;
	outfile__dynamic_array_spikemonitor_1_v.open("results\\_dynamic_array_spikemonitor_1_v_8980123394947442053", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_1_v.is_open())
	{
        if (! _dynamic_array_spikemonitor_1_v.empty() )
        {
			outfile__dynamic_array_spikemonitor_1_v.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_1_v[0]), _dynamic_array_spikemonitor_1_v.size()*sizeof(_dynamic_array_spikemonitor_1_v[0]));
		    outfile__dynamic_array_spikemonitor_1_v.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_1_v." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_2_i;
	outfile__dynamic_array_spikemonitor_2_i.open("results\\_dynamic_array_spikemonitor_2_i_-5315928828601514343", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_2_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_2_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_2_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_2_i[0]), _dynamic_array_spikemonitor_2_i.size()*sizeof(_dynamic_array_spikemonitor_2_i[0]));
		    outfile__dynamic_array_spikemonitor_2_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_2_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_2_t;
	outfile__dynamic_array_spikemonitor_2_t.open("results\\_dynamic_array_spikemonitor_2_t_-929440627957855383", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_2_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_2_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_2_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_2_t[0]), _dynamic_array_spikemonitor_2_t.size()*sizeof(_dynamic_array_spikemonitor_2_t[0]));
		    outfile__dynamic_array_spikemonitor_2_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_2_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_2_v;
	outfile__dynamic_array_spikemonitor_2_v.open("results\\_dynamic_array_spikemonitor_2_v_3540317612330304006", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_2_v.is_open())
	{
        if (! _dynamic_array_spikemonitor_2_v.empty() )
        {
			outfile__dynamic_array_spikemonitor_2_v.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_2_v[0]), _dynamic_array_spikemonitor_2_v.size()*sizeof(_dynamic_array_spikemonitor_2_v[0]));
		    outfile__dynamic_array_spikemonitor_2_v.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_2_v." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_3_i;
	outfile__dynamic_array_spikemonitor_3_i.open("results\\_dynamic_array_spikemonitor_3_i_2258128641724232409", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_3_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_3_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_3_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_3_i[0]), _dynamic_array_spikemonitor_3_i.size()*sizeof(_dynamic_array_spikemonitor_3_i[0]));
		    outfile__dynamic_array_spikemonitor_3_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_3_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_3_t;
	outfile__dynamic_array_spikemonitor_3_t.open("results\\_dynamic_array_spikemonitor_3_t_9123167462048295194", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_3_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_3_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_3_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_3_t[0]), _dynamic_array_spikemonitor_3_t.size()*sizeof(_dynamic_array_spikemonitor_3_t[0]));
		    outfile__dynamic_array_spikemonitor_3_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_3_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_3_v;
	outfile__dynamic_array_spikemonitor_3_v.open("results\\_dynamic_array_spikemonitor_3_v_-9125087113530255401", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_3_v.is_open())
	{
        if (! _dynamic_array_spikemonitor_3_v.empty() )
        {
			outfile__dynamic_array_spikemonitor_3_v.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_3_v[0]), _dynamic_array_spikemonitor_3_v.size()*sizeof(_dynamic_array_spikemonitor_3_v[0]));
		    outfile__dynamic_array_spikemonitor_3_v.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_3_v." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_4_i;
	outfile__dynamic_array_spikemonitor_4_i.open("results\\_dynamic_array_spikemonitor_4_i_7473364511458121524", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_4_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_4_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_4_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_4_i[0]), _dynamic_array_spikemonitor_4_i.size()*sizeof(_dynamic_array_spikemonitor_4_i[0]));
		    outfile__dynamic_array_spikemonitor_4_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_4_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_4_t;
	outfile__dynamic_array_spikemonitor_4_t.open("results\\_dynamic_array_spikemonitor_4_t_-8922979367694019382", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_4_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_4_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_4_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_4_t[0]), _dynamic_array_spikemonitor_4_t.size()*sizeof(_dynamic_array_spikemonitor_4_t[0]));
		    outfile__dynamic_array_spikemonitor_4_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_4_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_4_v;
	outfile__dynamic_array_spikemonitor_4_v.open("results\\_dynamic_array_spikemonitor_4_v_-6735026030360261806", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_4_v.is_open())
	{
        if (! _dynamic_array_spikemonitor_4_v.empty() )
        {
			outfile__dynamic_array_spikemonitor_4_v.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_4_v[0]), _dynamic_array_spikemonitor_4_v.size()*sizeof(_dynamic_array_spikemonitor_4_v[0]));
		    outfile__dynamic_array_spikemonitor_4_v.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_4_v." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_i;
	outfile__dynamic_array_spikemonitor_i.open("results\\_dynamic_array_spikemonitor_i_-1710665491708630177", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_i[0]), _dynamic_array_spikemonitor_i.size()*sizeof(_dynamic_array_spikemonitor_i[0]));
		    outfile__dynamic_array_spikemonitor_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_t;
	outfile__dynamic_array_spikemonitor_t.open("results\\_dynamic_array_spikemonitor_t_-331485698607636827", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_t[0]), _dynamic_array_spikemonitor_t.size()*sizeof(_dynamic_array_spikemonitor_t[0]));
		    outfile__dynamic_array_spikemonitor_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_v;
	outfile__dynamic_array_spikemonitor_v.open("results\\_dynamic_array_spikemonitor_v_-2647705156654610197", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_v.is_open())
	{
        if (! _dynamic_array_spikemonitor_v.empty() )
        {
			outfile__dynamic_array_spikemonitor_v.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_v[0]), _dynamic_array_spikemonitor_v.size()*sizeof(_dynamic_array_spikemonitor_v[0]));
		    outfile__dynamic_array_spikemonitor_v.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_v." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_1_t;
	outfile__dynamic_array_statemonitor_1_t.open("results\\_dynamic_array_statemonitor_1_t_-2328323351587757127", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_1_t.is_open())
	{
        if (! _dynamic_array_statemonitor_1_t.empty() )
        {
			outfile__dynamic_array_statemonitor_1_t.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_1_t[0]), _dynamic_array_statemonitor_1_t.size()*sizeof(_dynamic_array_statemonitor_1_t[0]));
		    outfile__dynamic_array_statemonitor_1_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_1_t." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_2_t;
	outfile__dynamic_array_statemonitor_2_t.open("results\\_dynamic_array_statemonitor_2_t_8778572233970779177", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_2_t.is_open())
	{
        if (! _dynamic_array_statemonitor_2_t.empty() )
        {
			outfile__dynamic_array_statemonitor_2_t.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_2_t[0]), _dynamic_array_statemonitor_2_t.size()*sizeof(_dynamic_array_statemonitor_2_t[0]));
		    outfile__dynamic_array_statemonitor_2_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_2_t." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_3_t;
	outfile__dynamic_array_statemonitor_3_t.open("results\\_dynamic_array_statemonitor_3_t_-3723465529603277730", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_3_t.is_open())
	{
        if (! _dynamic_array_statemonitor_3_t.empty() )
        {
			outfile__dynamic_array_statemonitor_3_t.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_3_t[0]), _dynamic_array_statemonitor_3_t.size()*sizeof(_dynamic_array_statemonitor_3_t[0]));
		    outfile__dynamic_array_statemonitor_3_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_3_t." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_4_t;
	outfile__dynamic_array_statemonitor_4_t.open("results\\_dynamic_array_statemonitor_4_t_-310849498278192541", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_4_t.is_open())
	{
        if (! _dynamic_array_statemonitor_4_t.empty() )
        {
			outfile__dynamic_array_statemonitor_4_t.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_4_t[0]), _dynamic_array_statemonitor_4_t.size()*sizeof(_dynamic_array_statemonitor_4_t[0]));
		    outfile__dynamic_array_statemonitor_4_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_4_t." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_t;
	outfile__dynamic_array_statemonitor_t.open("results\\_dynamic_array_statemonitor_t_3918872600994041348", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_t.is_open())
	{
        if (! _dynamic_array_statemonitor_t.empty() )
        {
			outfile__dynamic_array_statemonitor_t.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_t[0]), _dynamic_array_statemonitor_t.size()*sizeof(_dynamic_array_statemonitor_t[0]));
		    outfile__dynamic_array_statemonitor_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_t." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1__synaptic_post;
	outfile__dynamic_array_synapses_1__synaptic_post.open("results\\_dynamic_array_synapses_1__synaptic_post_-5344897800277649536", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_1__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_1__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1__synaptic_post[0]), _dynamic_array_synapses_1__synaptic_post.size()*sizeof(_dynamic_array_synapses_1__synaptic_post[0]));
		    outfile__dynamic_array_synapses_1__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1__synaptic_pre;
	outfile__dynamic_array_synapses_1__synaptic_pre.open("results\\_dynamic_array_synapses_1__synaptic_pre_-1863094791635734603", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_1__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_1__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1__synaptic_pre[0]), _dynamic_array_synapses_1__synaptic_pre.size()*sizeof(_dynamic_array_synapses_1__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_1__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_delay;
	outfile__dynamic_array_synapses_1_delay.open("results\\_dynamic_array_synapses_1_delay_6998036188863257139", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_delay.is_open())
	{
        if (! _dynamic_array_synapses_1_delay.empty() )
        {
			outfile__dynamic_array_synapses_1_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_delay[0]), _dynamic_array_synapses_1_delay.size()*sizeof(_dynamic_array_synapses_1_delay[0]));
		    outfile__dynamic_array_synapses_1_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_lastupdate;
	outfile__dynamic_array_synapses_1_lastupdate.open("results\\_dynamic_array_synapses_1_lastupdate_-5240511150580530340", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_1_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_1_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_lastupdate[0]), _dynamic_array_synapses_1_lastupdate.size()*sizeof(_dynamic_array_synapses_1_lastupdate[0]));
		    outfile__dynamic_array_synapses_1_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_N_incoming;
	outfile__dynamic_array_synapses_1_N_incoming.open("results\\_dynamic_array_synapses_1_N_incoming_6481834566887893352", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_1_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_1_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_N_incoming[0]), _dynamic_array_synapses_1_N_incoming.size()*sizeof(_dynamic_array_synapses_1_N_incoming[0]));
		    outfile__dynamic_array_synapses_1_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_N_outgoing;
	outfile__dynamic_array_synapses_1_N_outgoing.open("results\\_dynamic_array_synapses_1_N_outgoing_-4846275816696144397", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_1_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_1_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_N_outgoing[0]), _dynamic_array_synapses_1_N_outgoing.size()*sizeof(_dynamic_array_synapses_1_N_outgoing[0]));
		    outfile__dynamic_array_synapses_1_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_w;
	outfile__dynamic_array_synapses_1_w.open("results\\_dynamic_array_synapses_1_w_2101377667262957556", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_w.is_open())
	{
        if (! _dynamic_array_synapses_1_w.empty() )
        {
			outfile__dynamic_array_synapses_1_w.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_w[0]), _dynamic_array_synapses_1_w.size()*sizeof(_dynamic_array_synapses_1_w[0]));
		    outfile__dynamic_array_synapses_1_w.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_w." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2__synaptic_post;
	outfile__dynamic_array_synapses_2__synaptic_post.open("results\\_dynamic_array_synapses_2__synaptic_post_2797992051347620312", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_2__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_2__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2__synaptic_post[0]), _dynamic_array_synapses_2__synaptic_post.size()*sizeof(_dynamic_array_synapses_2__synaptic_post[0]));
		    outfile__dynamic_array_synapses_2__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2__synaptic_pre;
	outfile__dynamic_array_synapses_2__synaptic_pre.open("results\\_dynamic_array_synapses_2__synaptic_pre_-3423752270158303863", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_2__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_2__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2__synaptic_pre[0]), _dynamic_array_synapses_2__synaptic_pre.size()*sizeof(_dynamic_array_synapses_2__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_2__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_delay;
	outfile__dynamic_array_synapses_2_delay.open("results\\_dynamic_array_synapses_2_delay_6451194716812095572", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_delay.is_open())
	{
        if (! _dynamic_array_synapses_2_delay.empty() )
        {
			outfile__dynamic_array_synapses_2_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_delay[0]), _dynamic_array_synapses_2_delay.size()*sizeof(_dynamic_array_synapses_2_delay[0]));
		    outfile__dynamic_array_synapses_2_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_lastupdate;
	outfile__dynamic_array_synapses_2_lastupdate.open("results\\_dynamic_array_synapses_2_lastupdate_7894300358931146943", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_2_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_2_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_lastupdate[0]), _dynamic_array_synapses_2_lastupdate.size()*sizeof(_dynamic_array_synapses_2_lastupdate[0]));
		    outfile__dynamic_array_synapses_2_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_N_incoming;
	outfile__dynamic_array_synapses_2_N_incoming.open("results\\_dynamic_array_synapses_2_N_incoming_1190654134317045100", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_2_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_2_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_N_incoming[0]), _dynamic_array_synapses_2_N_incoming.size()*sizeof(_dynamic_array_synapses_2_N_incoming[0]));
		    outfile__dynamic_array_synapses_2_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_N_outgoing;
	outfile__dynamic_array_synapses_2_N_outgoing.open("results\\_dynamic_array_synapses_2_N_outgoing_4721751590411394462", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_2_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_2_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_N_outgoing[0]), _dynamic_array_synapses_2_N_outgoing.size()*sizeof(_dynamic_array_synapses_2_N_outgoing[0]));
		    outfile__dynamic_array_synapses_2_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_w;
	outfile__dynamic_array_synapses_2_w.open("results\\_dynamic_array_synapses_2_w_-1460739677678706621", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_w.is_open())
	{
        if (! _dynamic_array_synapses_2_w.empty() )
        {
			outfile__dynamic_array_synapses_2_w.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_w[0]), _dynamic_array_synapses_2_w.size()*sizeof(_dynamic_array_synapses_2_w[0]));
		    outfile__dynamic_array_synapses_2_w.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_w." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3__synaptic_post;
	outfile__dynamic_array_synapses_3__synaptic_post.open("results\\_dynamic_array_synapses_3__synaptic_post_-2408116559214037501", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_3__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_3__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3__synaptic_post[0]), _dynamic_array_synapses_3__synaptic_post.size()*sizeof(_dynamic_array_synapses_3__synaptic_post[0]));
		    outfile__dynamic_array_synapses_3__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3__synaptic_pre;
	outfile__dynamic_array_synapses_3__synaptic_pre.open("results\\_dynamic_array_synapses_3__synaptic_pre_-7034002654965885009", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_3__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_3__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3__synaptic_pre[0]), _dynamic_array_synapses_3__synaptic_pre.size()*sizeof(_dynamic_array_synapses_3__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_3__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_delay;
	outfile__dynamic_array_synapses_3_delay.open("results\\_dynamic_array_synapses_3_delay_6221293511767345203", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_delay.is_open())
	{
        if (! _dynamic_array_synapses_3_delay.empty() )
        {
			outfile__dynamic_array_synapses_3_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_delay[0]), _dynamic_array_synapses_3_delay.size()*sizeof(_dynamic_array_synapses_3_delay[0]));
		    outfile__dynamic_array_synapses_3_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_lastupdate;
	outfile__dynamic_array_synapses_3_lastupdate.open("results\\_dynamic_array_synapses_3_lastupdate_-6140443638593813919", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_3_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_3_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_lastupdate[0]), _dynamic_array_synapses_3_lastupdate.size()*sizeof(_dynamic_array_synapses_3_lastupdate[0]));
		    outfile__dynamic_array_synapses_3_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_N_incoming;
	outfile__dynamic_array_synapses_3_N_incoming.open("results\\_dynamic_array_synapses_3_N_incoming_5581250069174492357", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_3_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_3_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_N_incoming[0]), _dynamic_array_synapses_3_N_incoming.size()*sizeof(_dynamic_array_synapses_3_N_incoming[0]));
		    outfile__dynamic_array_synapses_3_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_N_outgoing;
	outfile__dynamic_array_synapses_3_N_outgoing.open("results\\_dynamic_array_synapses_3_N_outgoing_3990371741437791945", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_3_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_3_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_N_outgoing[0]), _dynamic_array_synapses_3_N_outgoing.size()*sizeof(_dynamic_array_synapses_3_N_outgoing[0]));
		    outfile__dynamic_array_synapses_3_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_w;
	outfile__dynamic_array_synapses_3_w.open("results\\_dynamic_array_synapses_3_w_-3509037240609652152", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_w.is_open())
	{
        if (! _dynamic_array_synapses_3_w.empty() )
        {
			outfile__dynamic_array_synapses_3_w.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_w[0]), _dynamic_array_synapses_3_w.size()*sizeof(_dynamic_array_synapses_3_w[0]));
		    outfile__dynamic_array_synapses_3_w.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_w." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4__synaptic_post;
	outfile__dynamic_array_synapses_4__synaptic_post.open("results\\_dynamic_array_synapses_4__synaptic_post_8182307610235124618", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_4__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_4__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4__synaptic_post[0]), _dynamic_array_synapses_4__synaptic_post.size()*sizeof(_dynamic_array_synapses_4__synaptic_post[0]));
		    outfile__dynamic_array_synapses_4__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4__synaptic_pre;
	outfile__dynamic_array_synapses_4__synaptic_pre.open("results\\_dynamic_array_synapses_4__synaptic_pre_1660970548303123614", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_4__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_4__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4__synaptic_pre[0]), _dynamic_array_synapses_4__synaptic_pre.size()*sizeof(_dynamic_array_synapses_4__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_4__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_delay;
	outfile__dynamic_array_synapses_4_delay.open("results\\_dynamic_array_synapses_4_delay_8270713345759489397", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_delay.is_open())
	{
        if (! _dynamic_array_synapses_4_delay.empty() )
        {
			outfile__dynamic_array_synapses_4_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_delay[0]), _dynamic_array_synapses_4_delay.size()*sizeof(_dynamic_array_synapses_4_delay[0]));
		    outfile__dynamic_array_synapses_4_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_lastupdate;
	outfile__dynamic_array_synapses_4_lastupdate.open("results\\_dynamic_array_synapses_4_lastupdate_5396914376571997500", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_4_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_4_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_lastupdate[0]), _dynamic_array_synapses_4_lastupdate.size()*sizeof(_dynamic_array_synapses_4_lastupdate[0]));
		    outfile__dynamic_array_synapses_4_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_N_incoming;
	outfile__dynamic_array_synapses_4_N_incoming.open("results\\_dynamic_array_synapses_4_N_incoming_-9143786746369433588", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_4_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_4_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_N_incoming[0]), _dynamic_array_synapses_4_N_incoming.size()*sizeof(_dynamic_array_synapses_4_N_incoming[0]));
		    outfile__dynamic_array_synapses_4_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_N_outgoing;
	outfile__dynamic_array_synapses_4_N_outgoing.open("results\\_dynamic_array_synapses_4_N_outgoing_5743893583357715797", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_4_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_4_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_N_outgoing[0]), _dynamic_array_synapses_4_N_outgoing.size()*sizeof(_dynamic_array_synapses_4_N_outgoing[0]));
		    outfile__dynamic_array_synapses_4_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_w;
	outfile__dynamic_array_synapses_4_w.open("results\\_dynamic_array_synapses_4_w_3492905619218015368", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_w.is_open())
	{
        if (! _dynamic_array_synapses_4_w.empty() )
        {
			outfile__dynamic_array_synapses_4_w.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_w[0]), _dynamic_array_synapses_4_w.size()*sizeof(_dynamic_array_synapses_4_w[0]));
		    outfile__dynamic_array_synapses_4_w.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_w." << endl;
	}
	ofstream outfile__dynamic_array_synapses__synaptic_post;
	outfile__dynamic_array_synapses__synaptic_post.open("results\\_dynamic_array_synapses__synaptic_post_3530272312714410228", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses__synaptic_post[0]), _dynamic_array_synapses__synaptic_post.size()*sizeof(_dynamic_array_synapses__synaptic_post[0]));
		    outfile__dynamic_array_synapses__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses__synaptic_pre;
	outfile__dynamic_array_synapses__synaptic_pre.open("results\\_dynamic_array_synapses__synaptic_pre_-1297354892816575945", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses__synaptic_pre[0]), _dynamic_array_synapses__synaptic_pre.size()*sizeof(_dynamic_array_synapses__synaptic_pre[0]));
		    outfile__dynamic_array_synapses__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_delay;
	outfile__dynamic_array_synapses_delay.open("results\\_dynamic_array_synapses_delay_-738406658835536075", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_delay.is_open())
	{
        if (! _dynamic_array_synapses_delay.empty() )
        {
			outfile__dynamic_array_synapses_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_delay[0]), _dynamic_array_synapses_delay.size()*sizeof(_dynamic_array_synapses_delay[0]));
		    outfile__dynamic_array_synapses_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_lastupdate;
	outfile__dynamic_array_synapses_lastupdate.open("results\\_dynamic_array_synapses_lastupdate_-2207206104741913375", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_lastupdate[0]), _dynamic_array_synapses_lastupdate.size()*sizeof(_dynamic_array_synapses_lastupdate[0]));
		    outfile__dynamic_array_synapses_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_N_incoming;
	outfile__dynamic_array_synapses_N_incoming.open("results\\_dynamic_array_synapses_N_incoming_-8350269211149257126", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_N_incoming[0]), _dynamic_array_synapses_N_incoming.size()*sizeof(_dynamic_array_synapses_N_incoming[0]));
		    outfile__dynamic_array_synapses_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_N_outgoing;
	outfile__dynamic_array_synapses_N_outgoing.open("results\\_dynamic_array_synapses_N_outgoing_8706767360983870089", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_N_outgoing[0]), _dynamic_array_synapses_N_outgoing.size()*sizeof(_dynamic_array_synapses_N_outgoing[0]));
		    outfile__dynamic_array_synapses_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_w;
	outfile__dynamic_array_synapses_w.open("results\\_dynamic_array_synapses_w_1538048628042318625", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_w.is_open())
	{
        if (! _dynamic_array_synapses_w.empty() )
        {
			outfile__dynamic_array_synapses_w.write(reinterpret_cast<char*>(&_dynamic_array_synapses_w[0]), _dynamic_array_synapses_w.size()*sizeof(_dynamic_array_synapses_w[0]));
		    outfile__dynamic_array_synapses_w.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_w." << endl;
	}

	ofstream outfile__dynamic_array_statemonitor_1_v;
	outfile__dynamic_array_statemonitor_1_v.open("results\\_dynamic_array_statemonitor_1_v_9003857160610182264", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_1_v.is_open())
	{
        for (int n=0; n<_dynamic_array_statemonitor_1_v.n; n++)
        {
            if (! _dynamic_array_statemonitor_1_v(n).empty())
            {
                outfile__dynamic_array_statemonitor_1_v.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_1_v(n, 0)), _dynamic_array_statemonitor_1_v.m*sizeof(_dynamic_array_statemonitor_1_v(0, 0)));
            }
        }
        outfile__dynamic_array_statemonitor_1_v.close();
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_1_v." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_2_v;
	outfile__dynamic_array_statemonitor_2_v.open("results\\_dynamic_array_statemonitor_2_v_2796640007027356381", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_2_v.is_open())
	{
        for (int n=0; n<_dynamic_array_statemonitor_2_v.n; n++)
        {
            if (! _dynamic_array_statemonitor_2_v(n).empty())
            {
                outfile__dynamic_array_statemonitor_2_v.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_2_v(n, 0)), _dynamic_array_statemonitor_2_v.m*sizeof(_dynamic_array_statemonitor_2_v(0, 0)));
            }
        }
        outfile__dynamic_array_statemonitor_2_v.close();
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_2_v." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_3_v;
	outfile__dynamic_array_statemonitor_3_v.open("results\\_dynamic_array_statemonitor_3_v_-4426069071135170544", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_3_v.is_open())
	{
        for (int n=0; n<_dynamic_array_statemonitor_3_v.n; n++)
        {
            if (! _dynamic_array_statemonitor_3_v(n).empty())
            {
                outfile__dynamic_array_statemonitor_3_v.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_3_v(n, 0)), _dynamic_array_statemonitor_3_v.m*sizeof(_dynamic_array_statemonitor_3_v(0, 0)));
            }
        }
        outfile__dynamic_array_statemonitor_3_v.close();
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_3_v." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_4_v;
	outfile__dynamic_array_statemonitor_4_v.open("results\\_dynamic_array_statemonitor_4_v_2290718986052836936", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_4_v.is_open())
	{
        for (int n=0; n<_dynamic_array_statemonitor_4_v.n; n++)
        {
            if (! _dynamic_array_statemonitor_4_v(n).empty())
            {
                outfile__dynamic_array_statemonitor_4_v.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_4_v(n, 0)), _dynamic_array_statemonitor_4_v.m*sizeof(_dynamic_array_statemonitor_4_v(0, 0)));
            }
        }
        outfile__dynamic_array_statemonitor_4_v.close();
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_4_v." << endl;
	}
	ofstream outfile__dynamic_array_statemonitor_v;
	outfile__dynamic_array_statemonitor_v.open("results\\_dynamic_array_statemonitor_v_-7119841891812010516", ios::binary | ios::out);
	if(outfile__dynamic_array_statemonitor_v.is_open())
	{
        for (int n=0; n<_dynamic_array_statemonitor_v.n; n++)
        {
            if (! _dynamic_array_statemonitor_v(n).empty())
            {
                outfile__dynamic_array_statemonitor_v.write(reinterpret_cast<char*>(&_dynamic_array_statemonitor_v(n, 0)), _dynamic_array_statemonitor_v.m*sizeof(_dynamic_array_statemonitor_v(0, 0)));
            }
        }
        outfile__dynamic_array_statemonitor_v.close();
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_statemonitor_v." << endl;
	}

	// Write profiling info to disk
	ofstream outfile_profiling_info;
	outfile_profiling_info.open("results/profiling_info.txt", ios::out);
	if(outfile_profiling_info.is_open())
	{
	outfile_profiling_info << "neurongroup_1_resetter_codeobject\t" << neurongroup_1_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_1_stateupdater_codeobject\t" << neurongroup_1_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_1_thresholder_codeobject\t" << neurongroup_1_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_resetter_codeobject\t" << neurongroup_2_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_stateupdater_codeobject\t" << neurongroup_2_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_thresholder_codeobject\t" << neurongroup_2_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_resetter_codeobject\t" << neurongroup_3_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_stateupdater_codeobject\t" << neurongroup_3_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_thresholder_codeobject\t" << neurongroup_3_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_resetter_codeobject\t" << neurongroup_4_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_stateupdater_codeobject\t" << neurongroup_4_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_thresholder_codeobject\t" << neurongroup_4_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_resetter_codeobject\t" << neurongroup_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_stateupdater_codeobject\t" << neurongroup_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_thresholder_codeobject\t" << neurongroup_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_1_codeobject\t" << spikemonitor_1_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_2_codeobject\t" << spikemonitor_2_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_3_codeobject\t" << spikemonitor_3_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_4_codeobject\t" << spikemonitor_4_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_codeobject\t" << spikemonitor_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "statemonitor_1_codeobject\t" << statemonitor_1_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "statemonitor_2_codeobject\t" << statemonitor_2_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "statemonitor_3_codeobject\t" << statemonitor_3_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "statemonitor_4_codeobject\t" << statemonitor_4_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "statemonitor_codeobject\t" << statemonitor_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_codeobject\t" << synapses_1_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_initialise_queue\t" << synapses_1_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_push_spikes\t" << synapses_1_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_synapses_create_generator_codeobject\t" << synapses_1_synapses_create_generator_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_codeobject\t" << synapses_2_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_initialise_queue\t" << synapses_2_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_push_spikes\t" << synapses_2_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_synapses_create_generator_codeobject\t" << synapses_2_synapses_create_generator_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_codeobject\t" << synapses_3_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_initialise_queue\t" << synapses_3_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_push_spikes\t" << synapses_3_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_synapses_create_generator_codeobject\t" << synapses_3_synapses_create_generator_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_codeobject\t" << synapses_4_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_initialise_queue\t" << synapses_4_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_push_spikes\t" << synapses_4_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_synapses_create_generator_codeobject\t" << synapses_4_synapses_create_generator_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_codeobject\t" << synapses_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_initialise_queue\t" << synapses_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_push_spikes\t" << synapses_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_synapses_create_generator_codeobject\t" << synapses_synapses_create_generator_codeobject_profiling_info << std::endl;
	outfile_profiling_info.close();
	} else
	{
	    std::cout << "Error writing profiling info to file." << std::endl;
	}

	// Write last run info to disk
	ofstream outfile_last_run_info;
	outfile_last_run_info.open("results/last_run_info.txt", ios::out);
	if(outfile_last_run_info.is_open())
	{
		outfile_last_run_info << (Network::_last_run_time) << " " << (Network::_last_run_completed_fraction) << std::endl;
		outfile_last_run_info.close();
	} else
	{
	    std::cout << "Error writing last run info to file." << std::endl;
	}
}

void _dealloc_arrays()
{
	using namespace brian;


	// static arrays
	if(_static_array__array_statemonitor_1__indices!=0)
	{
		delete [] _static_array__array_statemonitor_1__indices;
		_static_array__array_statemonitor_1__indices = 0;
	}
	if(_static_array__array_statemonitor_2__indices!=0)
	{
		delete [] _static_array__array_statemonitor_2__indices;
		_static_array__array_statemonitor_2__indices = 0;
	}
	if(_static_array__array_statemonitor_3__indices!=0)
	{
		delete [] _static_array__array_statemonitor_3__indices;
		_static_array__array_statemonitor_3__indices = 0;
	}
	if(_static_array__array_statemonitor_4__indices!=0)
	{
		delete [] _static_array__array_statemonitor_4__indices;
		_static_array__array_statemonitor_4__indices = 0;
	}
	if(_static_array__array_statemonitor__indices!=0)
	{
		delete [] _static_array__array_statemonitor__indices;
		_static_array__array_statemonitor__indices = 0;
	}
}

