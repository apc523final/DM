/*Euler.c
Method for integrating using forward Euler
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#include "euler.h"


//Constructor
Euler::Euler(double dt, Force &force)
  : dt_(dt),
    force_(force) {
}

//Destructor
Euler::~Euler() {
}

// Integrate particles' position and velocity for one time step.
int Euler::step(double t, Particle_vector &particles, Node_vector_element_pointer nodes) {
  force_.updateacceleration(nodes, particles); //Uses force function, update acceleration
  
//Loop over all particles and update velocity and position
  for (auto &p : particles) {
    p.x  += dt_ * p.vx;
    p.y  += dt_ * p.vy;

    p.vx += dt_ * p.ax;
    p.vy += dt_ * p.ay;

  }
  return 0;
}
