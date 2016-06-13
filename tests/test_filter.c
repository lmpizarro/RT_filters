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
   LPF_6db * lpf1;
   LPF_6db * lpf2;

   N = 44100;
   sr = 44100.0f;

   data = generate_step(N, N/10); 
   
   fc = 1.0f; 
   lpf1 = LPF_6db_C(fc, sr);
   lpf2 = LPF_6db_C(fc/1.55, sr);

   //printf("%f %f %f\n", lpf->coef1, lpf->coef2, lpf->a);

   for (i =0; i < N; i ++) {
    printf ("%f %f %f ", lpf1->minp, data[i], lpf1->mout);
    out =  LPF_6db_R (lpf2, LPF_6db_R (lpf1, data[i]));
    printf ("%f\n",  out);
   }

   LPF_6db_D(lpf1);
   LPF_6db_D(lpf2);
   free(data);
}


int test_hp_filter (){
   int N, i;
   float sr, fc, out;
   float * data;
   HPF_6db * hpf1;
   HPF_6db * hpf2;

   N = 44100;
   sr = 44100.0f;

   data = generate_step(N, N/10); 
   
   fc = 10.0f; 
   hpf1 = HPF_6db_C(fc, sr);
   hpf2 = HPF_6db_C(fc * 1.55f, sr);


   for (i =0; i < N; i ++) {
    printf ("%f %f %f ", hpf1->minp, data[i], hpf1->mout);
    out = HPF_6db_R(hpf2, HPF_6db_R (hpf1, data[i]));
    printf ("%f\n",  out);
   }

   HPF_6db_D(hpf1);
   HPF_6db_D(hpf2);
   free(data);

}

int test_hp12db_filter (){
   int N, i;
   float sr, fc, out, damp;
   float * data;
   HPF_12db_B * hpf1;

   N = 44100;
   sr = 44100.0f;

   data = generate_step(N, N/10); 
   
   fc = 10.0f; damp = 0.5f; 

   hpf1 =  HPF_12db_B_C(fc, damp, sr);

   printf("%f %f\n", hpf1->a1, hpf1->a2);
   for (i =0; i < N; i ++) {
    //printf ("%f %f %f ", hpf1->minp, data[i], hpf1->mout);
    //out = HPF_12db_B_R (hpf1, data[i]);
    //printf ("%f\n",  out);
   }


   HPF_12db_B_D(hpf1);
   free(data);
}

int main (){
   test_hp12db_filter();
   return (0);
}
