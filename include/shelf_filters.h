#ifndef _SHELF_FILTERS_H
#define _SHELF_FILTERS_H

#include "filters.h"

typedef struct {
   float fc;
   float sr;
   float warp;
   float q; //q factor
   float minp, mminp, mmminp, mmmminp;
   float mout, mmout, mmmout, mmmmout;
   float a0, a1, a2, a3, a4;
   float b0, b1, b2, b3, b4;
   LPF_12db *lpf;
   LS_Zeros_12db *lsz;
}Low_Shelf_12db;

Low_Shelf_12db *Low_Shelf_12db_C(const float fmin, const float sr, const float K);

#endif
