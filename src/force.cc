#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"


float main(Particle p1){
	//Set force equal to zero again	
	float force = 0;
	Particle_vector particles;
	RootNode root;
	int NumParticles = particles.size();


	/*Loop over all particles*/
	for(int i =0; i<NumParticles; i++){
		Particle p1 = particles[i]
		force += root.calculateforce(Particle p1) //calculate force
	}
	return force //return force
}

//Function that calculates force
float calculateforce(Particle p1){
	if NumParticles ==
		//force = F_G of particles, using findseparation
	//else
		//r=distance from nodes center of mass to TargetParticle
		//d=height of node
		//if (d/r < theta)
			//force = F_g of particel and center of mass of node
		//else
			//for all child nodes n
				//force += node.calculateforce(particle)



}
//Function that finds the separation between two particles
float findseparation(Particle p1, Paricle p2){
	separation = sqrt((p1.x - p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
	return separation;
}
