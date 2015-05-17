/*Euler.h
Header file for Euler method
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "force.h"
#include "node.h"


 //Forward Euler integrator.
class Euler : public Integrator {
 public:
  Euler(double dt, Force &force); //Constructor
  ~Euler(); //Destructor
  //Integrates one step forward using Forward Euler method
  int step(double t, Particle_vector &particles, Node_vector_element_pointer nodes);
 
 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
};

#endif  // EULER_H_
