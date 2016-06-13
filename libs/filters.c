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
 * HPF_6db
 */
HPF_6db *HPF_6db_C(const float fc, const float sr)
{
  
  float a0, a1, b0, b1, g;

  HPF_6db *new = (HPF_6db *)calloc(1, sizeof(HPF_6db));
  
  new->fc = fc;
  new->sr = sr;

  new->a = tan(PI * new->fc / new->sr);

  g = 1.0f;
  a0 = 1.0f;
  a1 = -a0; 


  b0 = 1.0f + new->a;
  b1 =  (1.0f - new->a);

  new->c0 = a0/ b0 ;
  new->c1 = a1 / b0;
  new->c2 = b1 / b0;

  new->minp = 0.0f;
  new->mout = 0.0f;

  return new;

}

float HPF_6db_R (HPF_6db *lp, float inp){
    float out;

    out = lp->c0 * inp + lp->c1 * lp->minp + lp->c2*lp->mout;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void HPF_6db_D(HPF_6db *hpf){
  free(hpf);
}

/*
 * HPF_12db
 */
HPF_12db *HPF_12db_C(const float fc, const float damp, const float sr)
{
  
  float Tc;

  HPF_12db *new = (HPF_12db *)calloc(1, sizeof(HPF_12db));
  
  new->fc = fc;
  new->sr = sr;
  new->d = damp;

  new->warp = tan(PI * new->fc / new->sr);
  Tc = tan(PI * new->fc / new->sr);


  new->beta = 0.5f * ((1.0f - new->d/(2*sin(Tc)))/(1.0f + new->d/(2*sin(Tc))));
  new->gamma = (0.5f + new->beta) * cos(Tc);
  new->alfa = (0.5f +new->beta + new->gamma)/4.0f;

  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}


float HPF_12db_R (HPF_12db *lp, float inp){
    float out;

    out = 2*(lp->alfa*(inp - 2*lp->minp + lp->mminp) + lp->gamma*lp->mout - lp->beta * lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void HPF_12db_D(HPF_12db *hpf){
  free(hpf);
}

HPF_12db_B *HPF_12db_B_C(const float fc, const float Q, const float sr)
{
  
  float K, W, DE;

  HPF_12db_B *new = (HPF_12db_B *)calloc(1, sizeof(HPF_12db_B));
  
  new->fc = fc;
  new->sr = sr;
  new->q = Q;

  K = tan(PI * new->fc / new->sr);
  new->warp = K;
  W = K * K;
  DE = 1 + K/Q + W;

  new->a1 = 2 * (W - 1) / DE;
  new->a2 = (1 - K/Q + W) / DE;
  new->b0 = 1 / DE;
  new->b1 = -2 * W / DE;
  new->b2 = new->b0;

  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}


float HPF_12db_B_R (HPF_12db_B *lp, float inp){
    float out;

    out = lp->b0 * inp + lp->b1 * lp->minp + lp->b2 * lp->mminp 
        - (lp->a1 * lp->mout + lp->a2* lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void HPF_12db_B_D(HPF_12db_B *hpf){
  free(hpf);
}
