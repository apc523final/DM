#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"

const double G = 6.67E-11; //Gravitational constant in m^3/kg*s^2
const float theta = 1; //Parameter for deciding when to calculate using COM or going to children nodes

/*NOTE TO FUTURE KRISTINA: USE: https://github.com/Nbodypp/HOW_final/blob/master/src/force_direct.cc
NEED TO FIX calculateforce function!
ALSO: FIX THE DANG HEADER FILE!
*/

//Force Constructor
Force::Force(int gravity/*=1*/)
  : gravity_(gravity) {
}

//Force Destructor
Force::~Force() {
}

//Function that calculates force
void Force::updateacceleration(Node_vector &n, Particle_vector &p){
	
	
	
	//Set acceleration to 0
  	for (auto &a : p) {
    		a.ax = 0.;
			a.ay = 0.;
    		// a.az = 0.;
	 }

	//Loop PROPERLY over particles and add to acceleration
	
	  double r, dax, day, daz,l, jx, jy, jmass;  // temp variables
	  for (auto i = p.begin(); i != p.end(); ++i) {
	    r = 0.;
	    dax = 0.;
	    day = 0.;
	    l=0.;
	    jx=0.;
	    jy=0.;
	    jmass=0.;
	    // daz = 0.;
	    for (auto j = n.begin(); j != n.end(); ++j) {
	      r = calculateseparation(*i, *j);
	      l = j->uppercorner-j->lowercorner;
	      if (l/r<theta){
	      	 jx = j->com[0];
	      	 jy = j->com[1];
	      	 jmass = j->mass;

	     	 dax = (jx - i->x) / pow(r, 3);
	     	 day = (jy - i->y) / pow(r, 3);
	     	 i->ax += jmass * dax;
	      	 i->ay += jmass * day;
	      }
	      else{
	      	Node_vector childs;
	      	for(int k=0; k<4; k++){
	      	Node child = *(j->children[k]);
	      	childs.push_back(child);
	      	}
	      	calculateforce(childs, p);
	      }
	    // jx = j->com[0];
	    // jy = j->com[1];
	    // jmass = j->mass;
              
	    // dax = (jx - i->x) / pow(r, 3);
	    // day = (jy - i->y) / pow(r, 3);
	      
	    // i->ax += jmass * dax;
	    // i->ay += jmass * day;
            }
            i->ax *= G;
            i->ay *= G;
          }
          
}

double calculateseparation(Particle &part, Node &nod){
    double jx, jy;
    jx = nod.com[0];
    jy = nod.com[1];
    return sqrt(pow((jx-part.x), 2) +
              pow((jy-part.y), 2));
}



