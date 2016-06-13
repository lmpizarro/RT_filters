#ifndef _RMS_H
#define _RMS_H

#include "filters.h"
#include "defs.h"

typedef struct {
   float fc;
   float sr;
   LPF_6db * filter1;
   LPF_6db * filter2;
}RMS_Filter;


RMS_Filter *RMS_Filter_C(const float fc, const float sr);
float RMS_Filter_R(RMS_Filter *rms, const float inp);
void RMS_Filter_D(RMS_Filter *rms);

#endif
