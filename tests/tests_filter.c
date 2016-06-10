#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../ladspa/util/filters.h"

//  gcc -o main tests.c  -lm -L../ladspa/util -lfilters


int test_rms ()
{

   float sr;
   int dur, N, i;
   low_pass_filter * lpf;
   rms_filter *rms;

   float a1, fc1, tx1, ty1, out1, x1, y1;

   float out2;


   dur = 2;
   sr = 44100.0f;

   N = dur * (int)sr;

   fc1 = 5.0f;
   a1 = tan(PI*fc1*sr);


   lpf = low_pass_filter_new(fc1, sr);
   rms = rms_filter_new(fc1, sr);
   printf ("parameter %f %f %d\n", a1, sr, N);

   x1 = 0.0f;
   y1 = 0.0f;
   float out3;
   for (i =0; i < N; i ++) {

    tx1 =  pow((sin(2*M_PI*1000*i/sr)),2);
    out2 = low_pass_filter_process (lpf, tx1);
    out3 = rms_filter_process(rms, tx1);
    out1 = (a1/(1+a1))*(tx1 + x1) - ((a1-1)/(1+a1))*y1;
    printf ("x1 %f, tx1 %f, out1 %f, out2 %f, out3 %f\n",x1, tx1, out1, out2, out3);
    y1 = out1;
    x1 = tx1;
   }

   low_pass_filter_free(lpf);
   rms_filter_free(rms);
   
   return(0);
}

int test_lp_filter (){
   int N, i;
   float sr, fc, out;
   float * data;
   low_pass_filter * lpf;

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
   lpf = low_pass_filter_new(fc, sr);

   //printf("%f %f %f\n", lpf->coef1, lpf->coef2, lpf->a);

   for (i =0; i < N; i ++) {
    printf ("%f %f %f ", lpf->minp, data[i], lpf->mout);
    out = low_pass_filter_process (lpf, data[i]);
    printf ("%f\n",  out);
   }

   low_pass_filter_free(lpf);
   free(data);
}

int main (){

   //test_rms();

   test_lp_filter();
   return (0);
}
