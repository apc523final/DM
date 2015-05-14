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
  double N = p.size(); //num particles
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

    cyclethroughnodes(n, *i, N);
    counter+=1;
    i->ax *= G;
    i->ay *= G;
  }
  
}

void Force::cyclethroughnodes(Node_vector_element_pointer n, Particle &i, double N){
  double r, dax, day, l, jx, jy, jmass, epsilon, d;
  d = 0.;
  epsilon = 0.;
  r = 0.;
  dax = 0.;
  day = 0.;
  l=0.;
  jx=0.;
  jy=0.;
  jmass=0.;
  for (auto j = n.begin(); j != n.end(); ++j) {
    if( (*j)->whatami == EMPTY)
      {
        continue;
      }
    r = calculateseparation(i, *j);
    if (use_softening){
        epsilon = 4/N;
    }
    if (r==0){
      //printf("#This is me! Proceed to next node please!\n");
      nodecounter+=1;
      continue;
    }

    l = (*j)->uppercorner[0]-(*j)->lowercorner[0];
    if ((l/r<theta) || ((*j)->whatami == LEAF)){
      jx = (*j)->com[0];
      jy = (*j)->com[1];
      jmass = (*j)->mass;
      d = sqrt(pow(r,2)+ pow(epsilon,2));

      dax = (jx - i.x) / pow(d, 3);
      day = (jy - i.y) / pow(d, 3);
      i.ax += jmass * dax;
      i.ay += jmass * day;
      nodecounter+=1;
    }
    else{
      Node_vector_element_pointer childs;
      for(int k=0; k<numchildren; k++){
        if ((*j)->children[k]==NULL){
          continue;
        }
        childs.push_back((*j)->children[k]);
      }
      cyclethroughnodes(childs, i, N);
    }

  }
  
}

double Force::calculateseparation(Particle &part, Node *nod)
{
  double jx_, jy_;
  jx_ = nod->com[0];
  jy_= nod->com[1];
  return sqrt(pow((part.x-jx_), 2) +
              pow((part.y-jy_), 2));
}
