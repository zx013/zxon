
#ifndef _BRIAN_OBJECTS_H
#define _BRIAN_OBJECTS_H

#include "synapses_classes.h"
#include "brianlib/clocks.h"
#include "brianlib/dynamic_array.h"
#include "brianlib/stdint_compat.h"
#include "network.h"
#include "randomkit.h"
#include<vector>


namespace brian {

// In OpenMP we need one state per thread
extern std::vector< rk_state* > _mersenne_twister_states;

//////////////// clocks ///////////////////
extern Clock defaultclock;
extern Clock statemonitor_1_clock;
extern Clock statemonitor_2_clock;
extern Clock statemonitor_3_clock;
extern Clock statemonitor_4_clock;
extern Clock statemonitor_clock;

//////////////// networks /////////////////
extern Network magicnetwork;
extern Network network;
extern Network network_1;
extern Network network_2;
extern Network network_3;
extern Network network_4;

//////////////// dynamic arrays ///////////
extern std::vector<int32_t> _dynamic_array_spikemonitor_1_i;
extern std::vector<double> _dynamic_array_spikemonitor_1_t;
extern std::vector<double> _dynamic_array_spikemonitor_1_v;
extern std::vector<int32_t> _dynamic_array_spikemonitor_2_i;
extern std::vector<double> _dynamic_array_spikemonitor_2_t;
extern std::vector<double> _dynamic_array_spikemonitor_2_v;
extern std::vector<int32_t> _dynamic_array_spikemonitor_3_i;
extern std::vector<double> _dynamic_array_spikemonitor_3_t;
extern std::vector<double> _dynamic_array_spikemonitor_3_v;
extern std::vector<int32_t> _dynamic_array_spikemonitor_4_i;
extern std::vector<double> _dynamic_array_spikemonitor_4_t;
extern std::vector<double> _dynamic_array_spikemonitor_4_v;
extern std::vector<int32_t> _dynamic_array_spikemonitor_i;
extern std::vector<double> _dynamic_array_spikemonitor_t;
extern std::vector<double> _dynamic_array_spikemonitor_v;
extern std::vector<double> _dynamic_array_statemonitor_1_t;
extern std::vector<double> _dynamic_array_statemonitor_2_t;
extern std::vector<double> _dynamic_array_statemonitor_3_t;
extern std::vector<double> _dynamic_array_statemonitor_4_t;
extern std::vector<double> _dynamic_array_statemonitor_t;
extern std::vector<int32_t> _dynamic_array_synapses_1__synaptic_post;
extern std::vector<int32_t> _dynamic_array_synapses_1__synaptic_pre;
extern std::vector<double> _dynamic_array_synapses_1_delay;
extern std::vector<double> _dynamic_array_synapses_1_lastupdate;
extern std::vector<int32_t> _dynamic_array_synapses_1_N_incoming;
extern std::vector<int32_t> _dynamic_array_synapses_1_N_outgoing;
extern std::vector<double> _dynamic_array_synapses_1_w;
extern std::vector<int32_t> _dynamic_array_synapses_2__synaptic_post;
extern std::vector<int32_t> _dynamic_array_synapses_2__synaptic_pre;
extern std::vector<double> _dynamic_array_synapses_2_delay;
extern std::vector<double> _dynamic_array_synapses_2_lastupdate;
extern std::vector<int32_t> _dynamic_array_synapses_2_N_incoming;
extern std::vector<int32_t> _dynamic_array_synapses_2_N_outgoing;
extern std::vector<double> _dynamic_array_synapses_2_w;
extern std::vector<int32_t> _dynamic_array_synapses_3__synaptic_post;
extern std::vector<int32_t> _dynamic_array_synapses_3__synaptic_pre;
extern std::vector<double> _dynamic_array_synapses_3_delay;
extern std::vector<double> _dynamic_array_synapses_3_lastupdate;
extern std::vector<int32_t> _dynamic_array_synapses_3_N_incoming;
extern std::vector<int32_t> _dynamic_array_synapses_3_N_outgoing;
extern std::vector<double> _dynamic_array_synapses_3_w;
extern std::vector<int32_t> _dynamic_array_synapses_4__synaptic_post;
extern std::vector<int32_t> _dynamic_array_synapses_4__synaptic_pre;
extern std::vector<double> _dynamic_array_synapses_4_delay;
extern std::vector<double> _dynamic_array_synapses_4_lastupdate;
extern std::vector<int32_t> _dynamic_array_synapses_4_N_incoming;
extern std::vector<int32_t> _dynamic_array_synapses_4_N_outgoing;
extern std::vector<double> _dynamic_array_synapses_4_w;
extern std::vector<int32_t> _dynamic_array_synapses__synaptic_post;
extern std::vector<int32_t> _dynamic_array_synapses__synaptic_pre;
extern std::vector<double> _dynamic_array_synapses_delay;
extern std::vector<double> _dynamic_array_synapses_lastupdate;
extern std::vector<int32_t> _dynamic_array_synapses_N_incoming;
extern std::vector<int32_t> _dynamic_array_synapses_N_outgoing;
extern std::vector<double> _dynamic_array_synapses_w;

//////////////// arrays ///////////////////
extern double *_array_defaultclock_dt;
extern const int _num__array_defaultclock_dt;
extern double *_array_defaultclock_t;
extern const int _num__array_defaultclock_t;
extern int64_t *_array_defaultclock_timestep;
extern const int _num__array_defaultclock_timestep;
extern int32_t *_array_neurongroup_1__spikespace;
extern const int _num__array_neurongroup_1__spikespace;
extern int32_t *_array_neurongroup_1_i;
extern const int _num__array_neurongroup_1_i;
extern double *_array_neurongroup_1_v;
extern const int _num__array_neurongroup_1_v;
extern int32_t *_array_neurongroup_2__spikespace;
extern const int _num__array_neurongroup_2__spikespace;
extern int32_t *_array_neurongroup_2_i;
extern const int _num__array_neurongroup_2_i;
extern double *_array_neurongroup_2_v;
extern const int _num__array_neurongroup_2_v;
extern int32_t *_array_neurongroup_3__spikespace;
extern const int _num__array_neurongroup_3__spikespace;
extern int32_t *_array_neurongroup_3_i;
extern const int _num__array_neurongroup_3_i;
extern double *_array_neurongroup_3_v;
extern const int _num__array_neurongroup_3_v;
extern int32_t *_array_neurongroup_4__spikespace;
extern const int _num__array_neurongroup_4__spikespace;
extern int32_t *_array_neurongroup_4_i;
extern const int _num__array_neurongroup_4_i;
extern double *_array_neurongroup_4_v;
extern const int _num__array_neurongroup_4_v;
extern int32_t *_array_neurongroup__spikespace;
extern const int _num__array_neurongroup__spikespace;
extern int32_t *_array_neurongroup_i;
extern const int _num__array_neurongroup_i;
extern double *_array_neurongroup_v;
extern const int _num__array_neurongroup_v;
extern int32_t *_array_spikemonitor_1__source_idx;
extern const int _num__array_spikemonitor_1__source_idx;
extern int32_t *_array_spikemonitor_1_count;
extern const int _num__array_spikemonitor_1_count;
extern int32_t *_array_spikemonitor_1_N;
extern const int _num__array_spikemonitor_1_N;
extern int32_t *_array_spikemonitor_2__source_idx;
extern const int _num__array_spikemonitor_2__source_idx;
extern int32_t *_array_spikemonitor_2_count;
extern const int _num__array_spikemonitor_2_count;
extern int32_t *_array_spikemonitor_2_N;
extern const int _num__array_spikemonitor_2_N;
extern int32_t *_array_spikemonitor_3__source_idx;
extern const int _num__array_spikemonitor_3__source_idx;
extern int32_t *_array_spikemonitor_3_count;
extern const int _num__array_spikemonitor_3_count;
extern int32_t *_array_spikemonitor_3_N;
extern const int _num__array_spikemonitor_3_N;
extern int32_t *_array_spikemonitor_4__source_idx;
extern const int _num__array_spikemonitor_4__source_idx;
extern int32_t *_array_spikemonitor_4_count;
extern const int _num__array_spikemonitor_4_count;
extern int32_t *_array_spikemonitor_4_N;
extern const int _num__array_spikemonitor_4_N;
extern int32_t *_array_spikemonitor__source_idx;
extern const int _num__array_spikemonitor__source_idx;
extern int32_t *_array_spikemonitor_count;
extern const int _num__array_spikemonitor_count;
extern int32_t *_array_spikemonitor_N;
extern const int _num__array_spikemonitor_N;
extern int32_t *_array_statemonitor_1__indices;
extern const int _num__array_statemonitor_1__indices;
extern double *_array_statemonitor_1_clock_dt;
extern const int _num__array_statemonitor_1_clock_dt;
extern double *_array_statemonitor_1_clock_t;
extern const int _num__array_statemonitor_1_clock_t;
extern int64_t *_array_statemonitor_1_clock_timestep;
extern const int _num__array_statemonitor_1_clock_timestep;
extern int32_t *_array_statemonitor_1_N;
extern const int _num__array_statemonitor_1_N;
extern double *_array_statemonitor_1_v;
extern const int _num__array_statemonitor_1_v;
extern int32_t *_array_statemonitor_2__indices;
extern const int _num__array_statemonitor_2__indices;
extern double *_array_statemonitor_2_clock_dt;
extern const int _num__array_statemonitor_2_clock_dt;
extern double *_array_statemonitor_2_clock_t;
extern const int _num__array_statemonitor_2_clock_t;
extern int64_t *_array_statemonitor_2_clock_timestep;
extern const int _num__array_statemonitor_2_clock_timestep;
extern int32_t *_array_statemonitor_2_N;
extern const int _num__array_statemonitor_2_N;
extern double *_array_statemonitor_2_v;
extern const int _num__array_statemonitor_2_v;
extern int32_t *_array_statemonitor_3__indices;
extern const int _num__array_statemonitor_3__indices;
extern double *_array_statemonitor_3_clock_dt;
extern const int _num__array_statemonitor_3_clock_dt;
extern double *_array_statemonitor_3_clock_t;
extern const int _num__array_statemonitor_3_clock_t;
extern int64_t *_array_statemonitor_3_clock_timestep;
extern const int _num__array_statemonitor_3_clock_timestep;
extern int32_t *_array_statemonitor_3_N;
extern const int _num__array_statemonitor_3_N;
extern double *_array_statemonitor_3_v;
extern const int _num__array_statemonitor_3_v;
extern int32_t *_array_statemonitor_4__indices;
extern const int _num__array_statemonitor_4__indices;
extern double *_array_statemonitor_4_clock_dt;
extern const int _num__array_statemonitor_4_clock_dt;
extern double *_array_statemonitor_4_clock_t;
extern const int _num__array_statemonitor_4_clock_t;
extern int64_t *_array_statemonitor_4_clock_timestep;
extern const int _num__array_statemonitor_4_clock_timestep;
extern int32_t *_array_statemonitor_4_N;
extern const int _num__array_statemonitor_4_N;
extern double *_array_statemonitor_4_v;
extern const int _num__array_statemonitor_4_v;
extern int32_t *_array_statemonitor__indices;
extern const int _num__array_statemonitor__indices;
extern double *_array_statemonitor_clock_dt;
extern const int _num__array_statemonitor_clock_dt;
extern double *_array_statemonitor_clock_t;
extern const int _num__array_statemonitor_clock_t;
extern int64_t *_array_statemonitor_clock_timestep;
extern const int _num__array_statemonitor_clock_timestep;
extern int32_t *_array_statemonitor_N;
extern const int _num__array_statemonitor_N;
extern double *_array_statemonitor_v;
extern const int _num__array_statemonitor_v;
extern int32_t *_array_synapses_1_N;
extern const int _num__array_synapses_1_N;
extern int32_t *_array_synapses_2_N;
extern const int _num__array_synapses_2_N;
extern int32_t *_array_synapses_3_N;
extern const int _num__array_synapses_3_N;
extern int32_t *_array_synapses_4_N;
extern const int _num__array_synapses_4_N;
extern int32_t *_array_synapses_N;
extern const int _num__array_synapses_N;

//////////////// dynamic arrays 2d /////////
extern DynamicArray2D<double> _dynamic_array_statemonitor_1_v;
extern DynamicArray2D<double> _dynamic_array_statemonitor_2_v;
extern DynamicArray2D<double> _dynamic_array_statemonitor_3_v;
extern DynamicArray2D<double> _dynamic_array_statemonitor_4_v;
extern DynamicArray2D<double> _dynamic_array_statemonitor_v;

/////////////// static arrays /////////////
extern int32_t *_static_array__array_statemonitor_1__indices;
extern const int _num__static_array__array_statemonitor_1__indices;
extern int32_t *_static_array__array_statemonitor_2__indices;
extern const int _num__static_array__array_statemonitor_2__indices;
extern int32_t *_static_array__array_statemonitor_3__indices;
extern const int _num__static_array__array_statemonitor_3__indices;
extern int32_t *_static_array__array_statemonitor_4__indices;
extern const int _num__static_array__array_statemonitor_4__indices;
extern int32_t *_static_array__array_statemonitor__indices;
extern const int _num__static_array__array_statemonitor__indices;

//////////////// synapses /////////////////
// synapses
extern SynapticPathway<double> synapses_pre;
// synapses_1
extern SynapticPathway<double> synapses_1_pre;
// synapses_2
extern SynapticPathway<double> synapses_2_pre;
// synapses_3
extern SynapticPathway<double> synapses_3_pre;
// synapses_4
extern SynapticPathway<double> synapses_4_pre;

// Profiling information for each code object
extern double neurongroup_1_resetter_codeobject_profiling_info;
extern double neurongroup_1_stateupdater_codeobject_profiling_info;
extern double neurongroup_1_thresholder_codeobject_profiling_info;
extern double neurongroup_2_resetter_codeobject_profiling_info;
extern double neurongroup_2_stateupdater_codeobject_profiling_info;
extern double neurongroup_2_thresholder_codeobject_profiling_info;
extern double neurongroup_3_resetter_codeobject_profiling_info;
extern double neurongroup_3_stateupdater_codeobject_profiling_info;
extern double neurongroup_3_thresholder_codeobject_profiling_info;
extern double neurongroup_4_resetter_codeobject_profiling_info;
extern double neurongroup_4_stateupdater_codeobject_profiling_info;
extern double neurongroup_4_thresholder_codeobject_profiling_info;
extern double neurongroup_resetter_codeobject_profiling_info;
extern double neurongroup_stateupdater_codeobject_profiling_info;
extern double neurongroup_thresholder_codeobject_profiling_info;
extern double spikemonitor_1_codeobject_profiling_info;
extern double spikemonitor_2_codeobject_profiling_info;
extern double spikemonitor_3_codeobject_profiling_info;
extern double spikemonitor_4_codeobject_profiling_info;
extern double spikemonitor_codeobject_profiling_info;
extern double statemonitor_1_codeobject_profiling_info;
extern double statemonitor_2_codeobject_profiling_info;
extern double statemonitor_3_codeobject_profiling_info;
extern double statemonitor_4_codeobject_profiling_info;
extern double statemonitor_codeobject_profiling_info;
extern double synapses_1_pre_codeobject_profiling_info;
extern double synapses_1_pre_initialise_queue_profiling_info;
extern double synapses_1_pre_push_spikes_profiling_info;
extern double synapses_1_synapses_create_generator_codeobject_profiling_info;
extern double synapses_2_pre_codeobject_profiling_info;
extern double synapses_2_pre_initialise_queue_profiling_info;
extern double synapses_2_pre_push_spikes_profiling_info;
extern double synapses_2_synapses_create_generator_codeobject_profiling_info;
extern double synapses_3_pre_codeobject_profiling_info;
extern double synapses_3_pre_initialise_queue_profiling_info;
extern double synapses_3_pre_push_spikes_profiling_info;
extern double synapses_3_synapses_create_generator_codeobject_profiling_info;
extern double synapses_4_pre_codeobject_profiling_info;
extern double synapses_4_pre_initialise_queue_profiling_info;
extern double synapses_4_pre_push_spikes_profiling_info;
extern double synapses_4_synapses_create_generator_codeobject_profiling_info;
extern double synapses_pre_codeobject_profiling_info;
extern double synapses_pre_initialise_queue_profiling_info;
extern double synapses_pre_push_spikes_profiling_info;
extern double synapses_synapses_create_generator_codeobject_profiling_info;

}

void _init_arrays();
void _load_arrays();
void _write_arrays();
void _dealloc_arrays();

#endif


