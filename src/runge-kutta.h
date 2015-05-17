/*runge-kutta.h
Header file for Runge-Kutta Method
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#ifndef RUNGE_KUTTA_H_
#define RUNGE_KUTTA_H_

#include "integrator.h"
#include "force.h"
#include "node.h"


class RungeKutta4 : public Integrator {
 public:
  RungeKutta4(const double dt, Force &force); //Constructor
  ~RungeKutta4(); //Destructor

//Integrates one step forward using Runge-Kutta method
  int step(double t, Particle_vector &p, Node_vector_element_pointer nodes);
 
 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
  Particle_vector k1, k2, k3, k4;   // intermediate states
};

#endif
