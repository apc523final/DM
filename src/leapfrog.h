/*leapfrog.h
Header file for Leapfrog method
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#ifndef LEAPFROG_H_
#define LEAPFROG_H_

#include "integrator.h"
#include "force.h"
#include "node.h"

class Leapfrog : public Integrator {
 public:
  Leapfrog(double dt, Force &force); //Constructor
  ~Leapfrog(); //Destructor
  //Integrates one step forward using Leapfrog Method
  int step(double t, Particle_vector &particles, Node_vector_element_pointer nodes);


 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
  void advance_vel(double dt, Particle_vector &particles); //advance velocity
};

#endif  // LEAPFROG_H_
