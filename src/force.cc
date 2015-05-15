/*force.cc
Force class*/


#include <stdio.h>
#include <math.h>
#include "node.h"
#include "particle.h"
#include "force.h"
#include <string>
#include "global.h"

//Initialize counters - used for tests
int counter = 0; //Num particles
int nodecounter = 0; //Num nodes

//Force Constructor
Force::Force()
{}

//Force Destructor
Force::~Force()
{}


//Function that updates acceleration
void Force::updateacceleration(Node_vector_element_pointer n, Particle_vector &p)
{
  double N = p.size(); //num particles input
  //Set acceleration to 0
  for (auto &a : p) {
    a.ax = 0.;
    a.ay = 0.;

  }

  //Loop over particles and add to acceleration

  for (auto i = p.begin(); i != p.end(); ++i) {

    cyclethroughnodes(n, *i, N);
    counter+=1;
    i->ax *= G;
    i->ay *= G;
  }
  
}

//Cycles through nodes and adds acceleration from each node on particle
void Force::cyclethroughnodes(Node_vector_element_pointer n, Particle &i, double N){
  //initialize temporary variables
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
  //Loop through nodes
  for (auto j = n.begin(); j != n.end(); ++j) {
    //If node has no particles, go to next node
    if( (*j)->whatami == EMPTY)
      {
        continue;
      }

    //Calculate distance between node COM and particle  
    r = calculateseparation(i, *j);

    //Apply softening parameter
    if (use_softening){
        if(N>100){
          epsilon = 4./N;
        }
        else{
          epsilon = 4.e-2;
        }
    }

    //If the node is the one containing the particle, go to
    //next node
    if (r==0){
      nodecounter+=1;
      continue;
    }
    //Calculate the length of the node
    l = (*j)->uppercorner[0]-(*j)->lowercorner[0];

    //See if node is far enough away to use COM approximation
    //or if node is already a leaf node, in which case
    //can also use COM
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

    //Else, find children nodes, and 
    //cycle through those nodes
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

//Calculates distance between a particle and the center of mass
//of a node
double Force::calculateseparation(Particle &part, Node *nod)
{
  double jx_, jy_;
  jx_ = nod->com[0];
  jy_= nod->com[1];
  return sqrt(pow((part.x-jx_), 2) +
              pow((part.y-jy_), 2));
}
