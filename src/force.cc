#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"
#include <string>
#include "global.h"

int counter = 0;
int nodecounter = 0;
/*NOTE TO FUTURE KRISTINA: USE: https://github.com/Nbodypp/HOW_final/blob/master/src/force_direct.cc
NEED TO FIX calculateforce function!
ALSO: FIX THE DANG HEADER FILE!
*/

//Force Constructor
Force::Force(int gravity/*=1*/)
  : gravity_(gravity)
{}

//Force Destructor
Force::~Force()
{}


//Function that calculates force
void Force::updateacceleration(Node_vector_element_pointer n, Particle_vector &p)
{
      	//Set acceleration to 0
  	for (auto &a : p) {
    		a.ax = 0.;
            a.ay = 0.;
    		// a.az = 0.;
	 }
	// for (auto i = p.begin(); i != p.end(); ++i){
 //    printf("Hi!, This is particle: %i\n", i);
 //  	}

	//Loop PROPERLY over particles and add to acceleration
	   // temp variables
	  for (auto i = p.begin(); i != p.end(); ++i) {

	    cyclethroughnodes(n, *i);
        counter+=1;
        i->ax *= G;
        i->ay *= G;
          }
          
}

void Force::cyclethroughnodes(Node_vector_element_pointer n, Particle &i){
  double r, dax, day, l, jx, jy, jmass; 
	r = 0.;
    dax = 0.;
    day = 0.;
    l=0.;
    jx=0.;
    jy=0.;
    jmass=0.;
  for (auto j = n.begin(); j != n.end(); ++j) {
	  // printf("This is particle %i\n", i);
	  printf("Number of particles done= %d, Number of nodes done= %d\n", counter, nodecounter);
	  //printf("Node is: %d\n", *j);
	  r = calculateseparation(i, *j);
	  printf("Seperation is %f\n", r);
	  if (r<1e-6){
	  	printf("This is me! Proceed to next node please!\n");
	  	dax = 0.;
	 	day = 0.;
	 	printf("Change in accel: %f, %f\n", dax, day);
	 	i.ax += jmass * dax;
	  	i.ay += jmass * day;
	  	nodecounter+=1;
	  	continue;
	  }
	  l = (*j)->uppercorner[0]-(*j)->lowercorner[0];
	  // printf("%f\n", l);
	  if ((l/r<theta) || ((*j)->whatami == LEAF)){
	  	 printf("Using center of mass\n");
	  	 jx = (*j)->com[0];
	  	 jy = (*j)->com[1];
	  	 jmass = (*j)->mass;

	 	 dax = (jx - i.x) / pow(r, 3);
	 	 day = (jy - i.y) / pow(r, 3);
	 	 printf("Change in accel: %f, %f\n", dax, day);
	 	 i.ax += jmass * dax;
	  	 i.ay += jmass * day;
	  	 nodecounter+=1;
	  }
	  else{
	  	printf("Time to find the children nodes \n");
	  	Node_vector_element_pointer childs;
	  	for(int k=0; k<numchildren; k++){
	  		if ((*j)->children[k]==NULL){
	  			continue;
	  		}
	  		childs.push_back((*j)->children[k]);
	  	}
	  	cyclethroughnodes(childs, i);
	  }
	// jx = j->com[0];
	// jy = j->com[1];
	// jmass = j->mass;
	      
	// dax = (jx - i->x) / pow(r, 3);
	// day = (jy - i->y) / pow(r, 3);
	  
	// i->ax += jmass * dax;
	// i->ay += jmass * day;
	}



}



double Force::calculateseparation(Particle &part, Node *nod)
{
     double jx_, jy_;
     jx_ = nod->com[0];
     jy_= nod->com[1];
    return sqrt(pow((jx_-part.x), 2) +
              pow((jy_-part.y), 2));
}
