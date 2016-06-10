#ifndef _DYNAMICS_H
#define _DYNAMICS_H

#include "defs.h"
#include "filters.h"


typedef struct {
   float fcAttack;
   float fcRelease;
   float attackState;
   float releaseState;
   float sr;
   LPF_6db * attackFilter;
   LPF_6db * releaseFilter;
}DYN_Filter;

DYN_Filter *DYN_Filter_C(const float attack_time, 
                                     const float release_time, const float sr);
void DYN_Filter_R (DYN_Filter *dyn, const float inpRMS, const float threshold);
void DYN_Filter_D(DYN_Filter *dyn);

void DYN_Filter_Set_Attack_Time (DYN_Filter *dyn, const float attack_time);
void DYN_Filter_Set_Release_Time (DYN_Filter *dyn, const float release_time);

float DYN_Filter_Get_Gain1 (DYN_Filter *dyn, const float gain_limit);

#endif
