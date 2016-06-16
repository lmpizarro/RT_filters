#include <stdio.h>

#include "shelf_filters.h"
#include "filters.h"
#include "t_util.h"

int main (){
  float fc = 1000.0f;
  float q = 1.0f;
  float sr = 44100.0f;
  float out;
  int i;
  Signals * s;

  LS_Zeros_12db * lsz;

  lsz = LS_Zeros_12db_C (fc, q, sr); 

  s = Signal_Sweep_Third_C(4.0f, sr); 

  fprintf(stdout, "as %f %f %f\n", lsz->a0, lsz->a1, lsz->a2 );
  fprintf(stdout, "bs %f %f %f\n", lsz->b0, lsz->b1, lsz->b2 );
   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", lsz->minp, s->data[i], lsz->mout);
    out = LS_Zeros_12db_R (lsz, s->data[i]);
    printf ("%f\n",  out);
   }


  LS_Zeros_12db_D(lsz);
  Signal_D(s);
  return 0;
}
