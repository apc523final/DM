/*integrator.h
Abstract integrator class*/

#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "particle.h"
#include "node.h"


class Integrator {
 public:
 	//Note: Constructors defined in each of the different
 	//integrator schemes
  virtual ~Integrator() {} //Destructor
  //Integrates one step forward using integrator of choice
  virtual int step(double t, Particle_vector &particles, Node_vector_element_pointer nodes) = 0;
};


#endif  //INTEGRATOR_H_
