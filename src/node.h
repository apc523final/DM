#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"
#include "particle.h"


class Node {
 public:
  //Node();
  Node(quad_octant_name quad_octant, double *lowercorner_, double *uppercorner_, Node_Type nodetype);
  ~Node();

  quad_octant_name quad_octant_;
  double *lowercorntemp;
  double *uppercorntemp;
  Node_Type whatami;
  double lowercorner[numdimen];
  double uppercorner[numdimen];

  double x_halfway;
  double y_halfway;

  Particle_vector_element_pointer particle_leaf;
  //int particle_number_leaf;

  double mass;    /**< mass of the particles in the node */
  double com[numdimen];

  //void FigureParticle(Particle passed_particle, int particle_number);
  void FigureParticle(Particle_vector_element_pointer passed_particle);
  Node *children[numchildren];
 
 private:
  //std::vector<Node *> children(4); /*pointer to the child nodes*/

  Node *BearChild(quad_octant_name quad_octant);

  quad_octant_name FigureQuadOctant(Particle particle_);

  void UpdateCOM(Particle passed_particle);

};

//typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
