#include <stdio.h>
#include <stdlib.h>
#include "dynamics.h"



int test_dyn_filters(){

   float Ts, dur;
   int  N, i, sr;
   float * data;

   dur = 1.0f;
   sr = 44100;
   Ts = 1.0f / sr;

   N = (int)(dur * sr);
   
   printf("Samples N  %d %f \n", N, Ts);

   data = (float *) calloc(N, sizeof(float));
 

   for (i = 0; i < N; i++){
       data[i] = 0.0f;
   } 

   for (i = N/5; i < 2*N/5; i++){
       data[i] = 0.7f;
   } 

   for (i = 2*N/5; i < 4*N/5; i++){
       data[i] = 0.2f;
   } 

   for (i = 4*N/5; i < 4*N/5; i++){
       data[i] = 0.5f;
   } 

   for (i = 4*N/5; i < 5*N/5; i++){
       data[i] = 0.2f;
   } 

   for (i = 0; i < N; i++){
      //printf("data %f\n", data[i]);
   }

   DYN_Filter *df;

   df = DYN_Filter_C(0.05f, 0.5f, sr);

   
   printf(" %f\n", df->fcAttack);
   printf(" %f\n", df->fcRelease);
   printf(" %f\n", df->attackState);
   printf(" %f\n", df->releaseState);
   printf(" %f\n", df->sr);


   for (i = 0; i < N; i++){
       float out = DYN_Filter_Get_Gain1(df, 0.7);
       DYN_Filter_R(df, data[i], 0.3f);
       printf ("%f %f %f\n",df->releaseState, df->attackState, out);
   }

   DYN_Filter_D(df);
   free(data);

}int main (){
   test_dyn_filters();
   return (0);
}
