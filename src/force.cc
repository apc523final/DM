#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"

const int G = 6.67E-11 //Gravitational constant in m^3/kg*s^2

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

void Force::main(Particle_vector &particles){
	calculateforce(particles)
}

//Function that calculates force
void Force::calculateforce(Particle_vector &p){
	//Find total number of particles
	int NumParticles = particles.size();
	
	//Set acceleration to 0
  	for (auto &a : p) {
    		a.ax = 0.;
		a.ay = 0.;
    		a.az = 0.;
	 }
	//Loop PROPERLY over particles and add to acceleration
	//in EACH direction.
	//FOLLOWING IS SEMYOUNG'S CODE
	/*
	  double r, dax, day, daz;  // temp variables
	  for (auto i = p.begin(); i != p.end(); ++i) {
	    r = 0.;
	    dax = 0.;
	    day = 0.;
	    daz = 0.;
	    for (auto j = i+1; j != p.end(); ++j) {
	      r = i->d(*j);
	      dax = (j->x - i->x) / pow(r, 3);
	      day = (j->y - i->y) / pow(r, 3);
	      daz = (j->z - i->z) / pow(r, 3);
	      // add to p_i and p_j with different signs
	      i->ax += j->mass * dax;
	      i->ay += j->mass * day;
	      i->az += j->mass * daz;
	      j->ax -= i->mass * dax;
	      j->ay -= i->mass * day;
	      j->az -= i->mass * daz;
	    }
	    i->ax *= G;
	    i->ay *= G;
	    i->az *= G;
	  }
	*/
	
	/* THE FOLLOWING IS OLD. WILL KEEP FOR NOW.
	if (NumParticles == 1){
		float r = findseparation(p1, p2)
		force = -G*p1.mass*p2.mass/pow(r,3) //Make a separate function for this?
	}
	else{
		Particle pm = root.com;
		float r = findseparation(p1, pm)
		float d = root.uppdercorner()-root.lowercorner()
		if (d/r < theta){
			//force = F_g of particle and center of mass of node
		}
		else{
			//for all child nodes n
				//force += node.calculateforce(particle)
		}
	}
	return force;
	*/

}
//Function that finds the separation between two particles - DO NOT NEED.
// float find3Dseparation(Particle p1, Particle p2){
// 	separation = sqrt((p1.x - p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
// 	return separation;
// }
