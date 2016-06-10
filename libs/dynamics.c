#include <stdlib.h>
#include "filters.h"
#include "dynamics.h"


/*
* DYN Filter
*/

DYN_Filter *DYN_Filter_C(const float attack_time, 
                                     const float release_time, 
                                     const float sr){

    
   DYN_Filter *new = (DYN_Filter *)calloc(1, sizeof(DYN_Filter));

   new->fcAttack = 1.0f/(2.0f * PI * attack_time);  
   new->fcRelease = 1.0f/(2.0f * PI * release_time);  
   new->sr = sr;
   new->attackState = 0.0f;
   new->releaseState = 0.0f;

   new->attackFilter = LPF_6db_C(new->fcAttack, new->sr);
   new->releaseFilter = LPF_6db_C(new->fcRelease, new->sr);

   return new;
}

void DYN_Filter_R (DYN_Filter *dyn, const float inpRMS, 
                               const float threshold){
    if (inpRMS >= threshold){
          dyn->attackState = LPF_6db_R(dyn->attackFilter, 1.0f); 
          dyn->releaseState = LPF_6db_R(dyn->releaseFilter, 0.0f); 
    }else{
          dyn->attackState = LPF_6db_R(dyn->attackFilter, 0.0f); 
          dyn->releaseState = LPF_6db_R(dyn->releaseFilter, 1.0f); 
    }
}

void DYN_Filter_D(DYN_Filter *dyn){
  LPF_6db_D(dyn->attackFilter);
  LPF_6db_D(dyn->releaseFilter);
  free(dyn);
}

void DYN_Filter_Set_Attack_Time (DYN_Filter *dyn, const float attack_time) {
    dyn->fcAttack = 1.0f / (attack_time * 2 * PI);
}

void DYN_Filter_Set_Release_Time (DYN_Filter *dyn, const float release_time) {
    dyn->fcRelease = 1.0f / (release_time *2 * PI);
}

float DYN_Filter_Get_Gain1 (DYN_Filter *dyn, const float gain) {
   float rel, att;
  
   att = dyn->attackState;  
   rel = dyn->releaseState;  
   return ((1.0f- gain)*rel + gain)*((gain - 1.0f)*att + 1.0f);
}


