/*runge-kutta.cc
Runge-Kutta method*/

#include "runge-kutta.h"

//Constructor
RungeKutta4::RungeKutta4(const double dt, Force &force)
  : dt_(dt),
    force_(force) {
}

//Destructor
RungeKutta4::~RungeKutta4()
{}

//Integrates one step forward using Runge-Kutta method
int RungeKutta4::step(double t, Particle_vector &p, Node_vector_element_pointer nodes) {
  k1 = p;
  force_.updateacceleration(nodes, k1);
  k2 = p;
  for (Particle_vector::size_type i = 0; i < p.size(); i++) {
    k2[i].x  += k1[i].vx * dt_ * 0.5;
    k2[i].y  += k1[i].vy * dt_ * 0.5;
    k2[i].vx += k1[i].ax * dt_ * 0.5;
    k2[i].vy += k1[i].ay * dt_ * 0.5;
  }
  force_.updateacceleration(nodes, k2);
  k3 = p;
  for (Particle_vector::size_type i = 0; i < p.size(); i++) {
    k3[i].x  += k2[i].vx * dt_ * 0.5;
    k3[i].y  += k2[i].vy * dt_ * 0.5;
    k3[i].vx += k2[i].ax * dt_ * 0.5;
    k3[i].vy += k2[i].ay * dt_ * 0.5;
  }
  force_.updateacceleration(nodes, k3);
  k4 = p;
  for (Particle_vector::size_type i = 0; i < p.size(); i++) {
    k4[i].x  += k3[i].vx * dt_;
    k4[i].y  += k3[i].vy * dt_;
    k4[i].vx += k3[i].ax * dt_;
    k4[i].vy += k3[i].ay * dt_;
  }
  force_.updateacceleration(nodes, k4);
  // update finally
  for (Particle_vector::size_type i = 0; i < p.size(); ++i) {
    p[i].x  = p[i].x  + (k1[i].vx + 2*k2[i].vx + 2*k3[i].vx + k4[i].vx)/6.*dt_;
    p[i].y  = p[i].y  + (k1[i].vy + 2*k2[i].vy + 2*k3[i].vy + k4[i].vy)/6.*dt_;
    p[i].vx = p[i].vx + (k1[i].ax + 2*k2[i].ax + 2*k3[i].ax + k4[i].ax)/6.*dt_;
    p[i].vy = p[i].vy + (k1[i].ay + 2*k2[i].ay + 2*k3[i].ay + k4[i].ay)/6.*dt_;
  }
  return 0;
}