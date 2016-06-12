#ifndef _FILTERS_H
#define _FILTERS_H

#include <math.h>

#define PI 3.14159265358979323846f


typedef struct {
   float fc;
   float a;
   float sr;
   float minp;
   float mout;
   float coef1;
   float coef2;

}LPF_6db;

LPF_6db *LPF_6db_C(const float fc, const float sr);
float LPF_6db_R (LPF_6db *lp, float inp);
void LPF_6db_D(LPF_6db *lpf);

typedef struct {
   float fc;
   float sr;
   LPF_6db * filter1;
   LPF_6db * filter2;
}RMS_Filter;


RMS_Filter *RMS_Filter_C(const float fc, const float sr);
float RMS_Filter_R (RMS_Filter *rms, const float inp);
void RMS_Filter_D(RMS_Filter *rms);

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
