#ifndef _MPREOPAMP_H
#define _MPREOPAMP_H

void calcTaus(float *coef);
void FeedBack(float *coef, const float T);
/*
 *  a = 7, b = 3000 * a
 *  K = 25000, 
 *
 *  coef0 = 0.0f coef1 = K coef2 = 0
 *  coef3 =  1 coef4 = a + b coef5 = a *b 
 * */
void Trafo(float *coef, const float T);
#endif


