#include "node.h"
#include "rootnode.h"
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



  RootNode root(lowercorner,uppercorner);
  Node sample(SW, lowercorner, uppercorner, ROOT);
  printf("Root limits: %lf %lf %lf %lf\n",root.lowercorner[0], root.lowercorner[1], root.uppercorner[0], root.uppercorner[1]);
  printf("NW corner: %lf %lf %lf %lf\n",root.children[NW]->lowercorner[0],root.children[NW]->lowercorner[1],root.children[NW]->uppercorner[0],root.children[NE]->uppercorner[1]);
  printf("NE corner: %lf %lf %lf %lf\n",root.children[NE]->lowercorner[0],root.children[NE]->lowercorner[1],root.children[NE]->uppercorner[0],root.children[NE]->uppercorner[1]);
  printf("SE corner: %lf %lf %lf %lf\n",root.children[SE]->lowercorner[0],root.children[SE]->lowercorner[1],root.children[SE]->uppercorner[0],root.children[SE]->uppercorner[1]);
  printf("SW corner: %lf %lf %lf %lf\n",root.children[SW]->lowercorner[0],root.children[SW]->lowercorner[1],root.children[SW]->uppercorner[0],root.children[SW]->uppercorner[1]);

  //RootNode root2(lowercorner, uppercorner);
  
  
  return 0;
}
