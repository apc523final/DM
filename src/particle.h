//Give proper credit to Semyeong

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>

class Particle {
 public:
  Particle();
  Particle(double mass, double x, double y);
  ~Particle();

  double mass;
  double x;
  double y;

  double ax;
  double ay;
};

typedef std::vector<Particle> Particle_vector;

typedef vector<Particle>::pointer Particle_vector_element_pointer;

#endif //PARTICLE_H_
