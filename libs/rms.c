#include <stdlib.h>
#include "filters.h"
#include "rms.h"
#include "filters.h"


/*
*   RMS filter
*/
RMS_Filter *RMS_Filter_C(const float fc, const float sr){

   RMS_Filter *new = (RMS_Filter *)calloc(1, sizeof(RMS_Filter));
   new->filter1 = LPF_6db_C(fc, sr);
   new->filter2 = LPF_6db_C(fc/2.0f, sr);
   return new;
}


float RMS_Filter_process (RMS_Filter *rms, const float inp){
  float out1, out2;

  out1 = LPF_6db_R(rms->filter1, inp);
  out2 = LPF_6db_R(rms->filter2, sqrt(out1));

  return out2*sqrt(2);
}

void RMS_Filter_D(RMS_Filter *rms){
  LPF_6db_D(rms->filter1);
  LPF_6db_D(rms->filter2);
  free(rms);
}


