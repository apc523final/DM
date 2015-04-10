//Give proper credit to Semyeong

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>

class Particle {
 public:
  Particle(double mass, double x, double y);
  ~Particle();

  double mass;
  double x;
  double y;

  double ax;
  double ay;
};

typedef std::vector<Particle> Particle_vector;

#endif //PARTICLE_H_
