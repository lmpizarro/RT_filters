#include <stdio.h>
#include <math.h>
#include "rms.h"


int test_rms ()
{

   float sr;
   int dur, N, i;
   RMS_Filter *rms;

   float a1, fc1, tx1, ty1, out1, x1, y1;

   float out2;


   dur = 2;
   sr = 44100.0f;

   N = dur * (int)sr;

   fc1 = 5.0f;
   a1 = tan(PI*fc1*sr);

   printf ("parameter %f %f %d\n", a1, sr, N);

   rms = RMS_Filter_C(fc1, sr);

   x1 = 0.0f;
   y1 = 0.0f;
   float out3;
   for (i =0; i < N; i ++) {

    tx1 =  pow((sin(2*M_PI*1000*i/sr)),2);

    out3 = RMS_Filter_R(rms, tx1);
    printf ("%f  %f  %f\n",x1, tx1, out3);
    y1 = out1;
    x1 = tx1;
   }

   RMS_Filter_D(rms);
   
   return(0);
}

int main (){
   test_rms();
   return (0);
}
