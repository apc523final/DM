#include "particle.h"

//Create an empty particle
Particle::Particle()
  : mass(0.),
    x(0.),
    y(0.),
    ax(0.),
    ay(0.)
{}

//Create a particle with these specific mass, x, and y values
Particle::Particle(double mass, double x, double y)
  : mass(mass),
    x(x),
    y(y),
    ax(0.),
    ay(0.)
{}

//Destructor
Particle::~Particle()
{}
