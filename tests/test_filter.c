#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "filters.h"

float *generate_step(const int N, const int init );

float *generate_step(const int N, const int init ){

   float * data;
   int i;

   data = (float *) calloc(N, sizeof(float));

   for (i = 0; i < init; i++){
      data[i] = 0.0f;
   } 

   for (i = init; i < N; i++){
      data[i] = 1.0f;
   } 

   return data;
}

int test_lp_filter (){
   int N, i;
   float sr, fc, out;
   float * data;
   LPF_6db * lpf;

   N = 44100;
   sr = 44100.0f;

   data = generate_step(N, N/10); 
   
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


int test_hp_filter (){
   int N, i;
   float sr, fc, out;
   float * data;
   HPF_6db * hpf;

   N = 44100;
   sr = 44100.0f;

   data = generate_step(N, N/10); 
   
   fc = 10.0f; 
   hpf = HPF_6db_C(fc, sr);

   //printf("%f %f %f\n", lpf->coef1, lpf->coef2, lpf->a);

   for (i =0; i < N; i ++) {
    printf ("%f %f %f ", hpf->minp, data[i], hpf->mout);
    out = HPF_6db_R (hpf, data[i]);
    printf ("%f\n",  out);
   }

   HPF_6db_D(hpf);
   free(data);

}

int main (){
   test_hp_filter();
   return (0);
}
