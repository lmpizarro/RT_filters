#include "mPreOpAmp.h"

/*
 *  T1 = C1 * R1, T2 = C2 *  R2, T3 = C1 * R2
 *                         Z2
 *         Z1         !----||----|
 *  --||--/\/\/\---!--!--/\/\/\--!--
 *
 * */

void calcTaus(float *coef){


        float R1, R2;
	float C1, C2;

	R1 = coef[0];
	C1 = coef[1];
	R2 = coef[2];
	C2 = coef[3];

	coef[0] = R1 * C1;
	coef[1] = R2 * C2;
	coef[2] = R2 * C1;
}

void FeedBack(float * coef,  const float T){

  float C; 
  float T1, T2, T3;
  float d, e;

  C = 2.0f / T;

  T1 = coef[0];
  T2 = coef[1];
  T3 = coef[2];
  e = 1.0f / (T1*T2); 
  d = (T1 + T2) * e;

  coef[0] = C*C + d * C + e ;
  coef[1] = -2.0f * C * C + 2.0f * e; 
  coef[2] = C*C - d * C + e; 

  d  = (T1 + T2 + T3) * e;
  coef[3] = C*C + d * C + e ;
  coef[4] = -2.0f * C * C + 2.0f * e; 
  coef[5] =  C*C - d * C + e; 
}


void Trafo(float *coef, const float T){

  float C; 
  float d, e;
  float K;
  C = 2.0f / T;

  K = coef[1];
  coef[0] = K * C;
  coef[1] = -coef[0];
  coef[2] = 0.0f;

  e = coef[5];
  d = coef[4];
  coef[3] = C + e + d * C;
  coef[4] = -2.0f * C + 2.0f * e; 
  coef[5] = C - d * C + e; 

}
