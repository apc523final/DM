/*euler_semi_implicit.h
Header file for Semi-Implicit Euler Integrator
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#ifndef EULER_SI_H_
#define EULER_SI_H_

#include "integrator.h"
#include "force.h"


class Euler_SI : public Integrator {
 public:
  Euler_SI(double dt, Force &force); //Constructor
  ~Euler_SI(); //Destuctor
  //Integrates one step forward using Semi-Implicit Euler method
  int step(double t, Particle_vector &particles, Node_vector_element_pointer nodes);
 
 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
};

#endif  // EULER_SI_H_
