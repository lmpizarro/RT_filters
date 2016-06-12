#include <stdio.h>
#include <stdlib.h>

#include "filters.h"

/*
* LP Filter
*/

LPF_6db *LPF_6db_C(const float fc, const float sr)
{

  LPF_6db *new = (LPF_6db *)calloc(1, sizeof(LPF_6db));
  
  new->fc = fc;
  new->sr = sr;

  new->a = tan(PI * new->fc / new->sr);
  new->coef1 = new->a/(1+new->a);
  new->coef2 = (new->a - 1)/(1 + new->a);

  new->minp = 0.0f;
  new->mout = 0.0f;

  return new;

}

float LPF_6db_R (LPF_6db *lp, float inp){
    float out;

    out = lp->coef1*(inp + lp->minp) - lp->coef2*lp->mout;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void LPF_6db_D(LPF_6db *lpf){
  free(lpf);
}


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

/*
* DYN Filter
*/

DYN_Filter *DYN_Filter_C(const float attack_time, 
                                     const float release_time, 
                                     const float sr){

    
   DYN_Filter *new = (DYN_Filter *)calloc(1, sizeof(DYN_Filter));

   new->fcAttack = 1.0f/(2.0f * PI * attack_time);  
   new->fcRelease = 1.0f/(2.0f * PI * release_time);  
   new->sr = sr;
   new->attackState = 0.0f;
   new->releaseState = 0.0f;

   new->attackFilter = LPF_6db_C(new->fcAttack, new->sr);
   new->releaseFilter = LPF_6db_C(new->fcRelease, new->sr);

   return new;
}
/*
void dynamics_filter_process (dynamics_filter *dyn, const float inpRMS, 
                               const float threshold){
    if (inpRMS >= threshold){
          dyn->attackState = low_pass_filter_process(dyn->attackFilter, 1.0f); 
          dyn->releaseState = low_pass_filter_process(dyn->releaseFilter, 0.0f); 
    }else{
          dyn->attackState = low_pass_filter_process(dyn->attackFilter, 0.0f); 
          dyn->releaseState = low_pass_filter_process(dyn->releaseFilter, 1.0f); 
    }
}

void dynamics_filter_free(dynamics_filter *dyn){
  low_pass_filter_free(dyn->attackFilter);
  low_pass_filter_free(dyn->releaseFilter);
  free(dyn);
}

void dynamics_filter_set_attack_time (dynamics_filter *dyn, const float attack_time) {
    dyn->fcAttack = 1.0f / (attack_time * 2 * PI);
}

void dynamics_filter_set_release_time (dynamics_filter *dyn, const float release_time) {
    dyn->fcRelease = 1.0f / (release_time *2 * PI);
}

float dynamics_filter_gain1 (dynamics_filter *dyn, const float gain) {
   float rel, att;
  
   att = dyn->attackState;  
   rel = dyn->releaseState;  
   return ((1.0f- gain)*rel + gain)*((gain - 1.0f)*att + 1.0f);
}
*/
