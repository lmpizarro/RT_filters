#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "filters.h"


int test_lp_filter (){
   int N, i;
   float sr, fc, out;
   float * data;
   LPF_6db * lpf;

   N = 44100;
   sr = 44100.0f;


   data = (float *) calloc(N, sizeof(float));
   
   for (i = 0; i < N/10; i++){
      data[i] = 0.0f;
   } 

   for (i = N/10; i < N; i++){
      data[i] = 1.0f;
   } 

   fc = 1.0f; 
   lpf = LPF_6db_C(fc, sr);

   //printf("%f %f %f\n", lpf->coef1, lpf->coef2, lpf->a);

   for (i =0; i < N; i ++) {
    printf ("%f %f %f ", lpf->minp, data[i], lpf->mout);
    out = LPF_6db_R (lpf, data[i]);
    printf ("%f\n",  out);
   }

   LPF_6db_D(lpf);
   free(data);
}

int main (){
   test_lp_filter();
   return (0);
}
