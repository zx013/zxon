#include "objects.h"
#include "code_objects/spikemonitor_codeobject.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>

////// SUPPORT CODE ///////
namespace {
 	
 inline int _brian_mod(int ux, int uy)
 {
     const int x = (int)ux;
     const int y = (int)uy;
     return ((x%y)+y)%y;
 }
 inline long _brian_mod(int ux, long uy)
 {
     const long x = (long)ux;
     const long y = (long)uy;
     return ((x%y)+y)%y;
 }
 inline long long _brian_mod(int ux, long long uy)
 {
     const long long x = (long long)ux;
     const long long y = (long long)uy;
     return ((x%y)+y)%y;
 }
 inline float _brian_mod(int ux, float uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(int ux, double uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(int ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long _brian_mod(long ux, int uy)
 {
     const long x = (long)ux;
     const long y = (long)uy;
     return ((x%y)+y)%y;
 }
 inline long _brian_mod(long ux, long uy)
 {
     const long x = (long)ux;
     const long y = (long)uy;
     return ((x%y)+y)%y;
 }
 inline long long _brian_mod(long ux, long long uy)
 {
     const long long x = (long long)ux;
     const long long y = (long long)uy;
     return ((x%y)+y)%y;
 }
 inline float _brian_mod(long ux, float uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(long ux, double uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long long _brian_mod(long long ux, int uy)
 {
     const long long x = (long long)ux;
     const long long y = (long long)uy;
     return ((x%y)+y)%y;
 }
 inline long long _brian_mod(long long ux, long uy)
 {
     const long long x = (long long)ux;
     const long long y = (long long)uy;
     return ((x%y)+y)%y;
 }
 inline long long _brian_mod(long long ux, long long uy)
 {
     const long long x = (long long)ux;
     const long long y = (long long)uy;
     return ((x%y)+y)%y;
 }
 inline float _brian_mod(long long ux, float uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(long long ux, double uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long long ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline float _brian_mod(float ux, int uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline float _brian_mod(float ux, long uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline float _brian_mod(float ux, long long uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline float _brian_mod(float ux, float uy)
 {
     const float x = (float)ux;
     const float y = (float)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(float ux, double uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(float ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(double ux, int uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(double ux, long uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(double ux, long long uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(double ux, float uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline double _brian_mod(double ux, double uy)
 {
     const double x = (double)ux;
     const double y = (double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(double ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, int uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, long uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, long long uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, float uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 inline long double _brian_mod(long double ux, long double uy)
 {
     const long double x = (long double)ux;
     const long double y = (long double)uy;
     return fmod(fmod(x, y)+y, y);
 }
 #ifdef _MSC_VER
 #define _brian_pow(x, y) (pow((double)(x), (y)))
 #else
 #define _brian_pow(x, y) (pow((x), (y)))
 #endif

}

////// HASH DEFINES ///////



void _run_spikemonitor_codeobject()
{
	using namespace brian;

    const std::clock_t _start_time = std::clock();

	///// CONSTANTS ///////////
	const int _numN = 1;
int32_t* const _array_spikemonitor_i = _dynamic_array_spikemonitor_i.empty()? 0 : &_dynamic_array_spikemonitor_i[0];
const int _numi = _dynamic_array_spikemonitor_i.size();
const int _num_source_v = 10;
const int _num_spikespace = 11;
const int _num_source_t = 1;
const int _num_source_i = 10;
double* const _array_spikemonitor_t = _dynamic_array_spikemonitor_t.empty()? 0 : &_dynamic_array_spikemonitor_t[0];
const int _numt = _dynamic_array_spikemonitor_t.size();
double* const _array_spikemonitor_v = _dynamic_array_spikemonitor_v.empty()? 0 : &_dynamic_array_spikemonitor_v[0];
const int _numv = _dynamic_array_spikemonitor_v.size();
const int _num_clock_t = 1;
const int _numcount = 10;
const int _num_source_idx = 10;
	///// POINTERS ////////////
 	
 int32_t*   _ptr_array_spikemonitor_N = _array_spikemonitor_N;
 int32_t* __restrict  _ptr_array_spikemonitor_i = _array_spikemonitor_i;
 double* __restrict  _ptr_array_neurongroup_v = _array_neurongroup_v;
 int32_t* __restrict  _ptr_array_neurongroup__spikespace = _array_neurongroup__spikespace;
 double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
 int32_t* __restrict  _ptr_array_neurongroup_i = _array_neurongroup_i;
 double* __restrict  _ptr_array_spikemonitor_t = _array_spikemonitor_t;
 double* __restrict  _ptr_array_spikemonitor_v = _array_spikemonitor_v;
 int32_t* __restrict  _ptr_array_spikemonitor_count = _array_spikemonitor_count;
 int32_t* __restrict  _ptr_array_spikemonitor__source_idx = _array_spikemonitor__source_idx;


	//// MAIN CODE ////////////

	int32_t _num_events = _ptr_array_neurongroup__spikespace[_num_spikespace-1];

    if (_num_events > 0)
    {
        int _start_idx = _num_events;
        int _end_idx = _num_events;
        for(int _j=0; _j<_num_events; _j++)
        {
            const int _idx = _ptr_array_neurongroup__spikespace[_j];
            if (_idx >= 0) {
                _start_idx = _j;
                break;
            }
        }
        for(int _j=_num_events-1; _j>=_start_idx; _j--)
        {
            const int _idx = _ptr_array_neurongroup__spikespace[_j];
            if (_idx < 10) {
                break;
            }
            _end_idx = _j;
        }
        _num_events = _end_idx - _start_idx;
        if (_num_events > 0) {
             const int _vectorisation_idx = 1;
                        

            for(int _j=_start_idx; _j<_end_idx; _j++)
            {
                const int _idx = _ptr_array_neurongroup__spikespace[_j];
                const int _vectorisation_idx = _idx;
                                
                const double _source_t = _ptr_array_defaultclock_t[0];
                const int32_t _source_i = _ptr_array_neurongroup_i[_idx];
                const double _source_v = _ptr_array_neurongroup_v[_idx];
                const double _to_record_t = _source_t;
                const double _to_record_v = _source_v;
                const int32_t _to_record_i = _source_i;

                _dynamic_array_spikemonitor_i.push_back(_to_record_i);
                _dynamic_array_spikemonitor_t.push_back(_to_record_t);
                _dynamic_array_spikemonitor_v.push_back(_to_record_v);
                _ptr_array_spikemonitor_count[_idx-0]++;
            }
            _ptr_array_spikemonitor_N[0] += _num_events;
        }
    }


    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    spikemonitor_codeobject_profiling_info += _run_time;
}

void _debugmsg_spikemonitor_codeobject()
{
	using namespace brian;
    const int _numN = 1;
int32_t* const _array_spikemonitor_i = _dynamic_array_spikemonitor_i.empty()? 0 : &_dynamic_array_spikemonitor_i[0];
const int _numi = _dynamic_array_spikemonitor_i.size();
const int _num_source_v = 10;
const int _num_spikespace = 11;
const int _num_source_t = 1;
const int _num_source_i = 10;
double* const _array_spikemonitor_t = _dynamic_array_spikemonitor_t.empty()? 0 : &_dynamic_array_spikemonitor_t[0];
const int _numt = _dynamic_array_spikemonitor_t.size();
double* const _array_spikemonitor_v = _dynamic_array_spikemonitor_v.empty()? 0 : &_dynamic_array_spikemonitor_v[0];
const int _numv = _dynamic_array_spikemonitor_v.size();
const int _num_clock_t = 1;
const int _numcount = 10;
const int _num_source_idx = 10;
        
    int32_t*   _ptr_array_spikemonitor_N = _array_spikemonitor_N;
    int32_t* __restrict  _ptr_array_spikemonitor_i = _array_spikemonitor_i;
    double* __restrict  _ptr_array_neurongroup_v = _array_neurongroup_v;
    int32_t* __restrict  _ptr_array_neurongroup__spikespace = _array_neurongroup__spikespace;
    double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
    int32_t* __restrict  _ptr_array_neurongroup_i = _array_neurongroup_i;
    double* __restrict  _ptr_array_spikemonitor_t = _array_spikemonitor_t;
    double* __restrict  _ptr_array_spikemonitor_v = _array_spikemonitor_v;
    int32_t* __restrict  _ptr_array_spikemonitor_count = _array_spikemonitor_count;
    int32_t* __restrict  _ptr_array_spikemonitor__source_idx = _array_spikemonitor__source_idx;

	std::cout << "Number of spikes: " << _ptr_array_spikemonitor_N[0] << endl;
}

