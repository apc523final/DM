#include "particle.h"
#include "node.h"


int main()
{
  numchildren = 4;
  
  Particle_vector particles;
  particles.push_back(Particle(1.0,1.0,1.0));
  particles.push_back(Particle(1.0,1.0,-1.0));
  particles.push_back(Particle(1.0,-1.0,-1.0));
  particles.push_back(Particle(1.0,-1.0,1.0));

  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-2.0;
  lowercorner[1]=-2.0;
  uppercorner[0]=2.0;
  uppercorner[1]=2.0;

  double firstparticleposition[2];
  firstparticleposition[0]=particles[0].x;
  firstparticleposition[1]=particles[0].y;


  Node(ROOT_,lowercorner,uppercorner,ROOT);
  
  
  return 0;
}
