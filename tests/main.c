#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ladspa.h"
#include "filters.h"


int test_rms ()
{

   float p;

   p = 2.0f;

   printf ("parameter %f \n", sqrt(p));
}

void main(){
  LPF_6db *lpf; 

  lpf = LPF_6db_C(5.0f, 44100.0f);
}
