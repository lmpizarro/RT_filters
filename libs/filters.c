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
LPF_12db *LPF_12db_C(const float fc, const float Q, const float sr, const float K)
{
  float W0, A, B, C, C2, alfa;

  LPF_12db *new = (LPF_12db *)calloc(1, sizeof(LPF_12db));

  new->fc = fc;
  new->sr = sr;
  new->q = Q;
  new->warp = 2 * sr * tan(PI * new->fc / new->sr);
  alfa = 1.0f / Q;

  //W0 = 2.0f * PI * fc;
  W0 = new->warp;
  A = W0 * W0;
  B = alfa * W0;
  C = 2.0f * new->sr;
  C2 = C * C; 
 
  new->a0 = K * A; 
  new->a1 = 2 * new->a0  ;
  new->a2 = new->a0;
  new->b0 = C2 + B*C + A ;
  new->b1 = 2*A -2*C2 ;
  new->b2 = C2 - B*C + A;

  new->a0 /= new->b0; 
  new->a1 /= new->b0;
  new->a2 /= new->b0;
  new->b1 /= new->b0;
  new->b2 /= new->b0;
  new->b0 /= new->b0;
  
  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}

void LPF_12db_Set_K(LPF_12db *new, const float K){

  float W0, A, B, C, C2;

  W0 = new->warp;
  A = W0 * W0;
  B = (1.0f / new->q) * W0;
  C = 2.0f * new->sr;
  C2 = C * C; 
 
  new->a0 = K * A; 
  new->a1 = 2 * new->a0  ;
  new->a2 = new->a0;
  new->b0 = C2 + B*C + A ;
  new->b1 = 2*A -2*C2 ;
  new->b2 = C2 - B*C + A;

  new->a0 /= new->b0; 
  new->a1 /= new->b0;
  new->a2 /= new->b0;
  new->b1 /= new->b0;
  new->b2 /= new->b0;
  new->b0 /= new->b0;
}

float LPF_12db_R (LPF_12db *lp, float inp){
    float out;

    out = lp->a0 * inp + lp->a1 * lp->minp + lp->a2 * lp->mminp 
        - (lp->b1 * lp->mout + lp->b2* lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void LPF_12db_D(LPF_12db *hpf){
  free(hpf);
}

/*
* zeros shelving
*/
LS_Zeros_12db *LS_Zeros_12db_C(const float fc, const float Q, const float sr){
  float W0, A, B, C, C2, alfa;

  LS_Zeros_12db *new = (LS_Zeros_12db *)calloc(1, sizeof(LS_Zeros_12db));

  new->fc = fc;
  new->sr = sr;
  new->q = Q;
  new->warp = 2 * sr * tan(PI * new->fc / new->sr);
  alfa = 1.0f / Q;

  //W0 = 2.0f * PI * fc;
  W0 = new->warp;
  A = W0 * W0;
  B = alfa * W0;
  C = 2.0f * new->sr;
  C2 = C * C; 
 
  new->b0 = A; 
  new->b1 = 2 * new->b0  ;
  new->b2 = new->b0;
  new->a0 = C2 + B*C + A ;
  new->a1 = 2*A -2*C2 ;
  new->a2 = C2 - B*C + A;

  new->a0 /= new->b0; 
  new->a1 /= new->b0;
  new->a2 /= new->b0;
  new->b1 /= new->b0;
  new->b2 /= new->b0;
  new->b0 /= new->b0;
  
  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}



float LS_Zeros_12db_R (LS_Zeros_12db *lp, float inp){
    float out;

    out = lp->a0 * inp + lp->a1 * lp->minp + lp->a2 * lp->mminp 
        - (lp->b1 * lp->mout + lp->b2* lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;

}

void LS_Zeros_12db_D(LS_Zeros_12db *lpf){
  free(lpf);
}




/*
* HPF
*/

HPF_12db_B *HPF_12db_B_C(const float fc, const float Q, const float sr)
{
  
  float K, W0, A, B, C, C2, alfa;

  HPF_12db_B *new = (HPF_12db_B *)calloc(1, sizeof(HPF_12db_B));
  
  new->fc = fc;
  new->sr = sr;
  new->q = Q;
  new->warp = 2 * sr * tan(PI * new->fc / new->sr);
  alfa = 1.0f / Q;

  //W0 = 2.0f * PI * fc;
  W0 = new->warp;
  A = W0 * W0;
  B = alfa * W0;
  K = 1.0f;
  C = 2.0f * new->sr;
  C2 = C * C; 
 
  new->a0 = K * C2; 
  new->a1 = -2 * new->a0  ;
  new->a2 = new->a0;
  new->b0 = C2 + B*C + A ;
  new->b1 = 2*A -2*C2 ;
  new->b2 = C2 - B*C + A;

  new->a0 /= new->b0; 
  new->a1 /= new->b0;
  new->a2 /= new->b0;
  new->b1 /= new->b0;
  new->b2 /= new->b0;
  new->b0 /= new->b0;

  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}


float HPF_12db_B_R (HPF_12db_B *lp, float inp){
    float out;

    out = lp->a0 * inp + lp->a1 * lp->minp + lp->a2 * lp->mminp 
        - (lp->b1 * lp->mout + lp->b2* lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void HPF_12db_B_D(HPF_12db_B *hpf){
  free(hpf);
}

/*
* BPF
*/

BPF_12db *BPF_12db_C(const float fc, const float Q, const float sr)
{
  
  float K, W0, A, B, C, C2, alfa;

  BPF_12db *new = (BPF_12db *)calloc(1, sizeof(BPF_12db));
  
  new->fc = fc;
  new->sr = sr;
  new->q = Q;
  new->warp = 2 * sr * tan(PI * new->fc / new->sr);
  alfa = 1.0f / Q;

  //W0 = 2.0f * PI * fc;
  W0 = new->warp;
  A = W0 * W0;
  B = alfa * W0;
  K = 1.0f;
  C = 2.0f * new->sr;
  C2 = C * C; 
 
  new->a0 = K * B * C; 
  new->a1 = 0.0f  ;
  new->a2 = -new->a0;
  new->b0 = C2 + B*C + A ;
  new->b1 = 2*A -2*C2 ;
  new->b2 = C2 - B*C + A;

  new->a0 /= new->b0; 
  new->a1 /= new->b0;
  new->a2 /= new->b0;
  new->b1 /= new->b0;
  new->b2 /= new->b0;
  new->b0 /= new->b0;

  new->minp = 0.0f;
  new->mout = 0.0f;
  new->mminp = 0.0f;
  new->mmout = 0.0f;

  return new;
}


float BPF_12db_R (BPF_12db *lp, float inp){
    float out;

    out = lp->a0 * inp + lp->a1 * lp->minp + lp->a2 * lp->mminp 
        - (lp->b1 * lp->mout + lp->b2* lp->mmout) ;
    lp->mmout = lp->mout;
    lp->mminp = lp->minp;
    lp->mout = out;
    lp->minp = inp;
    return out;
}

void BPF_12db_D(BPF_12db *hpf){
  free(hpf);
}
