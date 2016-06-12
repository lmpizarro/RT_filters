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
 * HPF
 */
HPF_6db *HPF_6db_C(const float fc, const float sr)
{
  
  float a0, a1, b0, b1, k;

  HPF_6db *new = (HPF_6db *)calloc(1, sizeof(HPF_6db));
  
  new->fc = fc;
  new->sr = sr;

  k = 1.0f;
  a0 = 2.0f * k;
  a1 = a0; 

  new->a = tan(PI * new->fc / new->sr);

  b0 = 2.0f + new->a/new->sr;
  b1 = -2.0f + new->a/new->sr;

  new->c0 = a0 / b0 ;
  new->c1 = a1 / b0;
  new->c2 = b1/ b0;

  new->minp = 0.0f;
  new->mout = 0.0f;

  return new;

}

float HPF_6db_R (HPF_6db *lp, float inp){
    float out;

    out = lp->c0 * inp + lp->c1 * lp->minp - lp->c2*lp->mout;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void HPF_6db_D(HPF_6db *hpf){
  free(hpf);
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

void DYN_Filter_R (DYN_Filter *dyn, const float inpRMS, 
                               const float threshold){
    if (inpRMS >= threshold){
          dyn->attackState = LPF_6db_R(dyn->attackFilter, 1.0f); 
          dyn->releaseState = LPF_6db_R(dyn->releaseFilter, 0.0f); 
    }else{
          dyn->attackState = LPF_6db_R(dyn->attackFilter, 0.0f); 
          dyn->releaseState = LPF_6db_R(dyn->releaseFilter, 1.0f); 
    }
}

void DYN_Filter_D(DYN_Filter *dyn){
  LPF_6db_D(dyn->attackFilter);
  LPF_6db_D(dyn->releaseFilter);
  free(dyn);
}

void DYN_Filter_Set_Attack_Time (DYN_Filter *dyn, const float attack_time) {
    dyn->fcAttack = 1.0f / (attack_time * 2 * PI);
}

void DYN_Filter_Set_Release_Time (DYN_Filter *dyn, const float release_time) {
    dyn->fcRelease = 1.0f / (release_time *2 * PI);
}

float DYN_Filter_Gain1 (DYN_Filter *dyn, const float gain) {
   float rel, att;
  
   att = dyn->attackState;  
   rel = dyn->releaseState;  
   return ((1.0f- gain)*rel + gain)*((gain - 1.0f)*att + 1.0f);
}
