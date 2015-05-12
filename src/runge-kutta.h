/**
 * @file
 *
 * @brief Runge-Kutta 4th order integrator
 */

#ifndef RUNGE_KUTTA_H_
#define RUNGE_KUTTA_H_

#include "integrator.h"
#include "force.h"
#include "node.h"

/**
 * @brief Runge-Kutta 4th order integrator
 */
class RungeKutta4 : public Integrator {
 public:
  RungeKutta4(const double dt, Force &force);
  ~RungeKutta4();
  int step(double t, Particle_vector &p, Node_vector_element_pointer nodes);
 private:
  const double dt_;       // timestep
  Force &force_;    // Force model
  Particle_vector k1, k2, k3, k4;   // intermediate states
};

#endif