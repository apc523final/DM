/*euler_semi_implicit.cc
Semi-Impliciti Euler Method
The code for this integration scheme was modified by us, borrowed from 
Joshua Wallace's APC 523 project of the previous semester; 
we give proper credit to his partners, Semyeong Oh and Cole Holcomb, with 
whom the original version of this code was developed in collaboration.*/

#include "euler_semi_implicit.h"
#include "particle.h"
#include "node.h"


//Constructor
Euler_SI::Euler_SI(double dt, Force &force)
  : dt_(dt),
    force_(force) {
}

//Destructor
Euler_SI::~Euler_SI() {
}

//Integrates one step forward using Semi-Implicit Euler method
int Euler_SI::step(double t, Particle_vector &particles, Node_vector_element_pointer nodes) {

  force_.updateacceleration(nodes, particles); //Use force method to update acceleration
  for (auto &p : particles) {
    // Calculate velocity
    p.vx += dt_ * p.ax;
    p.vy += dt_ * p.ay;
    // Calculate position using new, updated velocity
    p.x += dt_ * p.vx;
    p.y += dt_ * p.vy;
  }
  return 0;
}
