#include "particle.h"
#include "global.h"
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
    vx(0.),
    vy(0.),
    ax(0.),
    ay(0.)
{}

//Destructor
Particle::~Particle()
{}

/*
 * Print formatted position of all particles
 */
void print_particles(const Particle_vector &particles, std::ostream &f)
{
  //for printing the z-position, currently 0 for 2D case
  double zero = 0.0;

  //loop over all the particles
  for (const auto &p : particles)
    {
      f << std::scientific;
      f << p.x << ' '
        << p.y << ' '
        << zero << ' '; //Print out 0 for the z position
    }
  //f << '\n';
}


double total_energy(Particle_vector &particles)
{
  double energy = 0.;
  
  //loop over all the particles
  for(const auto &p : particles)
    {
      energy += .5 * p.mass * (p.vx * p.vx + p.vy * p.vy); //add kinetic energy of this particle

      //loop over all the other particles for potential energy calculation
      for(auto &p2 : particles)
        {
          if(&p2 != &p) //if they are not the same particles
            {
              energy += -G * p.mass * p2.mass / sqrt( pow((p.x-p2.x), 2) + pow((p.y-p2.y), 2)); //Add potential energy from the other particle
            }
        }
    }

  return energy;
}
