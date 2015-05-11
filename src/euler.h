
/**
 * @file euler.h
 * @brief Forward Euler integrator
 */

#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
#include "force.h"

/**
 * Forward Euler integrator.
 */
class Euler : public Integrator {
 public:
  Euler(double dt, const Force &force);
  ~Euler();
  int step(double t, Particle_vector &particles);
 private:
  const double dt_;       // timestep
  const Force &force_;    // Force model
};

#endif  // EULER_H_