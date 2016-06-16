#ifndef _SHELF_FILTERS_H
#define _SHELF_FILTERS_H


typedef struct {
   float fc;
   float sr;
   float warp;
   float q; //q factor
   float minp, mminp;
   float mout, mmout;
   float a0, a1, a2, a3;
   float b0, b1, b2, b3;
}Low_Shelf_12db;


Low_Shelf_12db *Low_Shelf_12db(const float fmin, const float sr){}


#endif
