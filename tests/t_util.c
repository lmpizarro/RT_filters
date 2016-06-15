#include <stdlib.h>
#include <math.h>


#include "t_util.h"


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



Signals *Signal_Step_C( const float length, const float init, const float sr){

   int i, N_init;
  
  Signals *new = (Signals *)calloc(1, sizeof(Signals));
  new->length = length;
  new->N = length * sr;
  new->sr = sr;
  new->data  = (float *)calloc(new->N, sizeof(float));
  N_init = init * sr;

  if (N_init < new->N){
    for (i = 0; i < N_init; i++){
      new->data[i] = 0.0f;
    } 

    for (i = N_init; i < new->N; i++){
      new->data[i] = 1.0f;
    } 
  } else{
    for (i = 0; i < new->N; i++){
      new->data[i] = 1.0f;
    } 
  }

  return new;
}

Signals *Signal_Sweep_C(float length, float sr){

  int i, j, kt;
  float Ts;
  float frecs[13] = {10,20,40,80,160,320,640,1280, 2560, 5120, 10240, 15000, 20000};

  Signals *new = (Signals *)calloc(1, sizeof(Signals));
  new->length = length;
  new->N = length * sr;
  new->sr = sr;
  new->data  = (float *)calloc(new->N, sizeof(float));
  Ts = 1.0f / new->sr;

  for(j=0; j<13; j++){
     for (i = 0; i<new->N/13; i++){
        kt =  j*(new->N/13) + i;
        new->data[kt] = sin(2*PI*frecs[j]*kt*Ts);
     }
  } 
  return new;
}

void Signal_D(Signals *s){
  free(s->data);
  free(s);
}


