#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cmath>

enum Node_Type{PARENT, LEAF, ROOT, EMPTY};
enum quad_octant_name{NW=0, NE, SE, SW, uNW=0, uNE, uSE, uSW, lNW, lNE, lSE, lSW, ROOT_=100};

const int numdimen = 2;
int numchildren;

/*if(numdimen == 2)
  {
    numchildren = 4;
  }
 else if(numdimen == 3)
   {
     numchildren = 8;
   }
 else
   {
     printf("WARNING! WARNING! Unknown number of dimensions defined!  It is %d\n",numdimen);
     }*/


#endif //GLOBAL_H_
