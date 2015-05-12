/*Defines the Particle class for storing information about the individual
  particles in the simulation.
  Special thanks to Semyeong Oh who developed the original prototype of this 
  class (in a project Joshua Wallace worked on), which we have adapted for 
  our purposes here.
*/

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include <iostream>

//The Particle class
class Particle {
 public:
  Particle();
  Particle(double mass, double x, double y);
  ~Particle();


  double mass; //mass of the particle
  double x;  //x-position of the particle
  double y;  //y-position of the particle

  double vx; //x-velocity of the particle
  double vy; //y-velocity of the particle

  double ax;  //x-direction acceleration of the particle
  double ay;  //y-direction acceleration of the particle

  double d(Particle &particle);
};

//Define a std::vector for storing many instances of Particle
typedef std::vector<Particle> Particle_vector;

//Define a pointer to a specific element of Particle_vector
//This pointer is also (roughly?) equivalent to Particle *
typedef std::vector<Particle>::pointer Particle_vector_element_pointer;

//This function will print the positions of all the particles
void print_particles(const Particle_vector &particles, std::ostream &f);

#endif //PARTICLE_H_
