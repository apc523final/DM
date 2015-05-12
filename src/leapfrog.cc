/**
 * @file leapfrog.cc
 * @brief Forward Euler integrator
 */

#include "leapfrog.h"

/**
 * Constructor.
 * @param dt timestep
 * @param force Force model
 */
Leapfrog::Leapfrog(double dt, Force &force)
  : dt_(dt),
    force_(force) {
}

Leapfrog::~Leapfrog() {
}

/**
 * Inegrate particles' position and velocity for one time step.
 */
int Leapfrog::step(double t, Particle_vector &particles, Node_vector_element_pointer nodes) {

  force_.updateacceleration(nodes, particles);
  advance_vel(0.5*dt_, particles);
  for (auto &ptmp : particles) {
    ptmp.x += dt_ * ptmp.vx;
    ptmp.y += dt_ * ptmp.vy;
  }
  force_.updateacceleration(nodes, particles);
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