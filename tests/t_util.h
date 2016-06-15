#ifndef _T_UTIL_H
#define _T_UTIL_H

#include "defs.h"



typedef struct {
   float sr;
   int N;
   float length; // in seconds
   float * data;
}Signals;

Signals *Signal_Step_C( const float length, const float init, const float sr);
Signals *Signal_Sweep_C(float length, float sr);
Signals *Signal_Sweep_Third_C(float length, float sr);
void Signal_D(Signals *s);


#endif
