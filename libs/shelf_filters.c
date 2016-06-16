#include <stdlib.h>

#include "filters.h"
#include "shelf_filters.h"


Low_Shelf_12db *Low_Shelf_12db_C(const float fmin, const float sr, const float K){


  LPF_12db *lpf;
  LS_Zeros_12db *lsz;  

  lpf = LPF_12db_C(fmin, 1.41f, sr, K);
  lsz = LS_Zeros_12db_C(2*fmin, 1.41f, sr);
 
  Low_Shelf_12db *new = (Low_Shelf_12db *)calloc(1, sizeof(Low_Shelf_12db));

  new->a0 = lpf->a0 * lsz->a0;
  new->a1 = lpf->a0 * lsz->a1 + lpf->a1 * lsz->a0;
  new->a2 = lpf->a0 * lsz->a2 + lpf->a1 * lsz->a1 + lpf->a2 * lsz->a0;
  new->a3 = lpf->a1 * lsz->a2 + lpf->a2 * lsz->a1;
  new->a4 = lpf->a2 * lsz->a2;

  new->a0 = lpf->b0 * lsz->b0;
  new->a1 = lpf->b0 * lsz->b1 + lpf->b1 * lsz->b0;
  new->a2 = lpf->b0 * lsz->b2 + lpf->b1 * lsz->b1 + lpf->b2 * lsz->b0;
  new->a3 = lpf->b1 * lsz->b2 + lpf->b2 * lsz->b1;
  new->a4 = lpf->b2 * lsz->b2;

  LS_Zeros_12db_D(lsz); 
  LPF_12db_D(lpf); 

  return new;
}


