/**
 * @file leapfrog.h
 * @brief Leapfrog integrator
 */

#ifndef LEAPFROG_H_
#define LEAPFROG_H_

#include "integrator.h"
#include "force.h"
#include "node.h"

/**
 * Leapfrog second order integrator.
 */
class Leapfrog : public Integrator {
 public:
  Leapfrog(double dt, Force &force);
  ~Leapfrog();
  int step(double t, Particle_vector &particles, Node_vector_element_pointer nodes);
 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
  void advance_vel(double dt, Particle_vector &particles);
};

#endif  // LEAPFROG_H_