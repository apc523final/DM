#include "particle.h"


Particle::Particle(double mass, double x, double y)
  : mass(mass),
    x(x),
    y(y),
    ax(0.),
    ay(0.)
{}

Particle::~Particle()
{}
