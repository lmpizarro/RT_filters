#include "utils.h"

/*
 * UTILS
 */



float DW (const float i1, const float fi1, float alfa){

     if (alfa < 0.0f) alfa = 0.0f;
     if (alfa > 1.0f) alfa = 1.0f;
     return i1 * (1-alfa) + fi1 * alfa;
}
