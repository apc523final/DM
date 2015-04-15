#include "node.h"
//#include "rootnode.h"
#include "particle.h"

int main()
{
  //numchildren = 4;
  
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



  //RootNode root(lowercorner,uppercorner);
  Node root(SW, lowercorner, uppercorner, ROOT);
  printf("%lf %lf %lf %lf\n",root.lowercorner[0], root.lowercorner[1], root.uppercorner[0], root.uppercorner[1]);

  //RootNode root2(lowercorner, uppercorner);
  
  
  return 0;
}
