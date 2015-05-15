/* force.h 
Header file for the force calculation code*/


#ifndef FORCE_H_
#define FORCE_H_

#include <vector>
#include "global.h"
#include "particle.h"
#include "node.h"


/*Define functions used in Force class*/

class Force {
 public:
  Force(); //Constructor
  ~Force(); //Destructor


//Updates acceleration for each particle in particle vector
  void updateacceleration(Node_vector_element_pointer n, Particle_vector &p);

//Cycles through nodes to find the acceleration
  void cyclethroughnodes(Node_vector_element_pointer n, Particle &p, double N);

//Calculates the distance between a particle and the center of mass of the node
  double calculateseparation(Particle &p, Node *n);

};


#endif //FORCE_H_
