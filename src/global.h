/* Some parameters and stuff that are useful to declare globally.
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cmath>

/*Defines the types of nodes that exist*/
enum Node_Type{PARENT, LEAF, EMPTY, ROOT=10};

/*Defines the different quadrants/octants each node can have
 NW =  negative x, positive y; NE = positive x and y; 
 SE = positive x and negative y; SW = negative x and y
 u = upper, which means positive z; l = lower, which means negative z
 u/l names are used for the 3-dimensional case, NOT u/l is for 
 2-dimensional case
 ROOT node is no quadrant of another node, so ROOT_ corresponds to this
 ERROR_ is for returning errors when a function needs to return a 
 quad_octant_name and wants to return an error*/
enum quad_octant_name{NW=0, NE, SE, SW, uNW=0, uNE, uSE, uSW, lNW, lNE, lSE, lSW, ROOT_=100, ERROR_=-1};

/* Number of dimensions */
const int numdimen = 2;

/*Based on number of dimensions, set the number of children*/
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
const int numchildren = 4;

const double theta = 1.; //Parameter for deciding when to calculate using COM or going to children nodes

const double G = 1.;

const double rmin = 1e-1;

const double dx = .1; //Used in courant condition

const double C = 1; //Courant number

const bool use_softening = true; //Use softening parameter


#endif //GLOBAL_H_
