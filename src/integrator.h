/**
 * @file integrator.h
 * @brief Abstract Integrator class
 */

#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "particle.h"
#include "node.h"

/**
 * Abstract integrator class.
 */
class Integrator {
 public:
  virtual ~Integrator() {}
  virtual int step(double t, Particle_vector &particles, Node_vector &nodes) = 0;
};


#endif  //INTEGRATOR_H_