#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "filters.h"
#include "t_util.h"


int test_sweep_lp6(){
  Signals *s;
  float sr = 44100;
  int i;
  LPF_6db * lpf1;
  float fc = 40.0f;
  float out;

  s = Signal_Sweep_C(4.0f, sr); 

  lpf1 = LPF_6db_C(fc, sr);

  for (i = 0; i < s->N; i++){
     fprintf(stdout, "%f", s->data[i]);
     out = LPF_6db_R (lpf1, s->data[i]);
     fprintf(stdout, "  %f\n", out);
  }
 
  LPF_6db_D(lpf1);
  Signal_D(s);
  return 0;
}

int test_lp_filter (){
   int i;
   float sr, fc, out;
   LPF_6db * lpf1;
   LPF_6db * lpf2;
   Signals *s;

   sr = 44100.0f;

   s = Signal_Step_C(1.0f, 0.5f, sr); 
   
   fc = 1.0f; 
   lpf1 = LPF_6db_C(fc, sr);
   lpf2 = LPF_6db_C(fc/1.55, sr);

   //printf("%f %f %f\n", lpf->coef1, lpf->coef2, lpf->a);

   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", lpf1->minp, s->data[i], lpf1->mout);
    out =  LPF_6db_R (lpf2, LPF_6db_R (lpf1, s->data[i]));
    printf ("%f\n",  out);
   }

   LPF_6db_D(lpf1);
   LPF_6db_D(lpf2);
   Signal_D(s);
}


int test_hp_filter (){
   int i;
   float sr, fc, out;
   HPF_6db * hpf1;
   HPF_6db * hpf2;
   Signals * s;

   sr = 44100.0f;

   s = Signal_Step_C(1.0f, 0.5f, sr); 

   fc = 10.0f; 
   hpf1 = HPF_6db_C(fc, sr);
   hpf2 = HPF_6db_C(fc * 1.55f, sr);


   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", hpf1->minp, s->data[i], hpf1->mout);
    out = HPF_6db_R(hpf2, HPF_6db_R (hpf1, s->data[i]));
    printf ("%f\n",  out);
   }

   HPF_6db_D(hpf1);
   HPF_6db_D(hpf2);
   Signal_D(s);

}

int test_hp12db_filter (){
   int i;
   float sr, fc, out, damp;
   HPF_12db_B * hpf1;
   Signals * s;

   sr = 44100.0f;

   s = Signal_Step_C(1.0f, 0.5f, sr); 
   
   fc = 10000.0f; damp = 0.5f; 

   hpf1 =  HPF_12db_B_C(fc, damp, sr);

   //printf("a0 %f a1 %fi a2 %f\n", hpf1->a0, hpf1->a1, hpf1->a2);
   //printf("b0 %f b1 %f b2 %f\n", hpf1->b0, hpf1->b1, hpf1->b2);
   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", hpf1->minp, s->data[i], hpf1->mout);
    out = HPF_12db_B_R (hpf1, s->data[i]);
    printf ("%f\n",  out);
   }

   HPF_12db_B_D(hpf1);
   Signal_D(s);
}

int test_hp12db_Sweep_filter (){
   int i;
   float sr, fc, out, damp;
   HPF_12db_B * hpf1;
   Signals * s;

   sr = 44100.0f;

   s = Signal_Sweep_Third_C(4.0f, sr); 
   
   fc = 75.0f; damp = 0.5f; 

   hpf1 =  HPF_12db_B_C(fc, damp, sr);

   //printf("a0 %f a1 %fi a2 %f\n", hpf1->a0, hpf1->a1, hpf1->a2);
   //printf("b0 %f b1 %f b2 %f\n", hpf1->b0, hpf1->b1, hpf1->b2);
   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", hpf1->minp, s->data[i], hpf1->mout);
    out = HPF_12db_B_R (hpf1, s->data[i]);
    printf ("%f\n",  out);
   }

   HPF_12db_B_D(hpf1);
   Signal_D(s);
}




int test_lp12db_filter (){
   int N, i;
   float sr, fc, out, damp;
   LPF_12db * hpf1;
   Signals * s;

   sr = 44100.0f;

   s = Signal_Step_C(1.0f, 0.5f, sr); 
 
   
   fc = 10.0f; damp = 0.5f; 

   hpf1 =  LPF_12db_C(fc, damp, sr);

   //printf("a0 %f a1 %fi a2 %f\n", hpf1->a0, hpf1->a1, hpf1->a2);
   //printf("b0 %f b1 %f b2 %f\n", hpf1->b0, hpf1->b1, hpf1->b2);
   for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", hpf1->minp, s->data[i], hpf1->mout);
    out = LPF_12db_R (hpf1, s->data[i]);
    printf ("%f\n",  out);
   }


   LPF_12db_D(hpf1);
   Signal_D(s);
}

int test_sweep_third_lp12 (){
  Signals *s;
  float sr;
  int i;

  sr = 44100.0f;
  s = Signal_Sweep_Third_C(4.0f, sr); 
  for (i = 0; i < s->N; i++){
     fprintf(stdout, "  %f\n", s->data[i]);
  }
  Signal_D(s);
  return 0;
}

int test_sweep_lp12(){
  Signals *s;
  float sr = 44100;
  int i;
  LPF_12db * lpf1;
  float fc = 40.0f;
  float out, q;

  q = 1.0;
  s = Signal_Sweep_C(4.0f, sr); 

  lpf1 = LPF_12db_C(fc, q, sr);

  for (i = 0; i < s->N; i++){
     fprintf(stdout, "%f", s->data[i]);
     out = LPF_12db_R (lpf1, s->data[i]);
     fprintf(stdout, "  %f\n", out);
  }

  LPF_12db_D(lpf1);
  Signal_D(s);
  return 0;
}


int test_bp12db_filter (){
  int i;
  float sr, fc, out, damp;
  float * data;
  BPF_12db * hpf1;
  Signals *s;

  sr = 44100.0f;

  s = Signal_Step_C(1.0f, 0.5f, sr); 
   
  fc = 10.0f; damp = 0.5f; 

  hpf1 =  BPF_12db_C(fc, damp, sr);

  //printf("a0 %f a1 %fi a2 %f\n", hpf1->a0, hpf1->a1, hpf1->a2);
  //printf("b0 %f b1 %f b2 %f\n", hpf1->b0, hpf1->b1, hpf1->b2);
  for (i =0; i < s->N; i ++) {
    printf ("%f %f %f ", hpf1->minp, s->data[i], hpf1->mout);
    out = BPF_12db_R (hpf1, s->data[i]);
    printf ("%f\n",  out);
  }


  BPF_12db_D(hpf1);
  Signal_D(s);
}



int main (){
   //test_hp12db_filter();
   //test_bp12db_filter();
   //test_lp12db_filter();
   //test_sweep_lp6();
   //test_sweep_lp12();
   //test_sweep_third();
   test_hp12db_Sweep_filter();
   return (0);
}
