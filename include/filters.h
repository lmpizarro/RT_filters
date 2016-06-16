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
   float warp;
   float q; //q factor
   float minp, mminp;
   float mout, mmout;
   float a0, a1, a2;
   float b0, b1, b2;

}LPF_12db;

LPF_12db *LPF_12db_C(const float fc, const float damp, const float sr, const float K);
float LPF_12db_R (LPF_12db *lp, float inp);
void LPF_12db_D(LPF_12db *lpf);
void LPF_12db_Set_K(LPF_12db *lp, const float K);

typedef struct {
   float fc;
   float sr;
   float warp;
   float q; //q factor
   float minp, mminp;
   float mout, mmout;
   float a0, a1, a2;
   float b0, b1, b2;

}LS_Zeros_12db;

LS_Zeros_12db *LS_Zeros_12db_C(const float fc, const float damp, const float sr);
float LS_Zeros_12db_R (LS_Zeros_12db *lp, float inp);
void LS_Zeros_12db_D(LS_Zeros_12db *lpf);




typedef struct {
   float fc;
   float sr;
   float warp;
   float q; //q factor
   float minp, mminp;
   float mout, mmout;
   float a0, a1, a2;
   float b0, b1, b2;
}HPF_12db_B;

HPF_12db_B *HPF_12db_B_C(const float fc, const float damp, const float sr);
float HPF_12db_B_R (HPF_12db_B *lp, float inp);
void HPF_12db_B_D(HPF_12db_B *lpf);

typedef struct {
   float fc;
   float sr;
   float warp;
   float q; //q factor
   float minp, mminp;
   float mout, mmout;
   float a0, a1, a2;
   float b0, b1, b2;
}BPF_12db;

BPF_12db *BPF_12db_C(const float fc, const float damp, const float sr);
float BPF_12db_R (BPF_12db *lp, float inp);
void BPF_12db_D(BPF_12db *lpf);

#endif
