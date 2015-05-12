#include "particle.h"
#include <cmath>

//Create an empty particle
Particle::Particle()
  : mass(0.),
    x(0.),
    y(0.),
    vx(0.),
    vy(0.),
    ax(0.),
    ay(0.)
{}

//Create a particle with these specific mass, x, and y values
Particle::Particle(double mass, double x, double y)
  : mass(mass),
    x(x),
    y(y),
    vx(x),
    vy(y),
    ax(0.),
    ay(0.)
{}

//Destructor
Particle::~Particle()
{}


//Calculate the distance between two particles.
double Particle::d(Particle &p) {
  return sqrt(pow((p.x-this->x), 2) +
              pow((p.y-this->y), 2));
}


/*
 * Print formatted position of all particles
 */
void print_particles(const Particles &particles, std::ostream &f) {
  for (const auto &p : particles) {
    f << std::scientific;
    f << p.x << ' '
      << p.y << ' ';
  }
  f << '\n';
}
