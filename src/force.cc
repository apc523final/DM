#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"


float main(){

//force=0;
/*Loop over all particles*/

	// force = RootNode.CalculateForceFromTree(particle)
	// end loop
}
float calculateforce(Particle p1){
	// if number of particles equals 1
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

float findseparation(Particle p1, Paricle p2){
	separation = sqrt((p1.x - p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
	return separation;
}
