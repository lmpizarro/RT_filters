#ifndef _FILTERS_H
#define _FILTERS_H

#include <math.h>

#include "defs.h"

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
   float a;
   float sr;
   float minp;
   float mout;
   float c0;
   float c1;
   float c2;

}HPF_6db;

HPF_6db *HPF_6db_C(const float fc, const float sr);
float HPF_6db_R (HPF_6db *lp, float inp);
void HPF_6db_D(HPF_6db *lpf);

typedef struct {
   float fc;
   float sr;
   LPF_6db * filter1;
   LPF_6db * filter2;
}RMS_Filter;


RMS_Filter *RMS_Filter_C(const float fc, const float sr);
float RMS_Filter_R (RMS_Filter *rms, const float inp);
void RMS_Filter_D(RMS_Filter *rms);

#endif
