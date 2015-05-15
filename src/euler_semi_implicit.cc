/*euler_semi_implicit.cc
Semi-Impliciti Euler Method*/

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

//Integrates one step forward using Forward Euler method
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