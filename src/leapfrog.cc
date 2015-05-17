/*leapfrog.cc
Leapfrog Method
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#include "leapfrog.h"

//Constructor
Leapfrog::Leapfrog(double dt, Force &force)
  : dt_(dt),
    force_(force) {
}

//Destructor
Leapfrog::~Leapfrog() {
}

//Integrates one step forward using Leapfrog method
int Leapfrog::step(double t, Particle_vector &particles, Node_vector_element_pointer nodes) {

  force_.updateacceleration(nodes, particles); //Use Force method to update acceleration
  advance_vel(0.5*dt_, particles); //advance velocities by a half step
  //find half-way positions
  for (auto &ptmp : particles) {
    ptmp.x += dt_ * ptmp.vx;
    ptmp.y += dt_ * ptmp.vy;
  }

  force_.updateacceleration(nodes, particles); //update acceleration again
  advance_vel(0.5*dt_, particles);  // sync vel with position
  return 0;
}

// advance velocity by dt
void Leapfrog::advance_vel(double dt, Particle_vector &particles) {
  for (auto &ptmp : particles) {
    ptmp.vx += dt * ptmp.ax;
    ptmp.vy += dt * ptmp.ay;
  }
}
