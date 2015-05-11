#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"

const int G = 6.67E-11 //Gravitational constant in m^3/kg*s^2
const float theta = 1 //Parameter for deciding when to calculate using COM or going to children nodes

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

void Force::main(Node_vector &nodes, Particle_vector &particles){
	calculateforce(nodes, particles);
}

//Function that calculates force
void Force::calculateforce(Node_vector &n, Particle_vector &p){
	
	
	
	//Set acceleration to 0
  	for (auto &a : p) {
    		a.ax = 0.;
			a.ay = 0.;
    		// a.az = 0.;
	 }

	//Loop PROPERLY over particles and add to acceleration
	//in EACH direction.
	//FOLLOWING IS SEMYOUNG'S CODE
	
	  double r, dax, day, daz;  // temp variables
	  for (auto i = p.begin(); i != p.end(); ++i) {
	    r = 0.;
	    dax = 0.;
	    day = 0.;
	    // daz = 0.;
	    for (auto j = n.begin(); j != n.end(); ++j) {
	      r = i->d(*j);
	      l = j.uppercorner-j.lowercorner;
	      if (l/r<theta){
	      	continue 
	      }
	      else{
	      	child = n.children
	      	calculateforce(&child, &p)
	      	break
	      }
	      j->x = j.com[0];
	      j->y = j.com[1];
	      j->mass = j.mass;

	      dax = (j->x - i->x) / pow(r, 3);
	      day = (j->y - i->y) / pow(r, 3);
	      // daz = (j->z - i->z) / pow(r, 3);
	      // add to p_i and p_j with different signs
	      i->ax += j->mass * dax;
	      i->ay += j->mass * day;
	      // i->az += j->mass * daz;
	      j->ax -= i->mass * dax;
	      j->ay -= i->mass * day;
	      // j->az -= i->mass * daz;
	    }
	    i->ax *= G;
	    i->ay *= G;
	    // i->az *= G;
	  }

}
