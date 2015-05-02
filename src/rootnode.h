#ifndef ROOTNODE_H_
#define ROOTNODE_H_

#include <vector>
#include "global.h"
#include "node.h"
#include "particle.h"

/*The RootNode class*/
class RootNode {
 public:
  RootNode(double *lowercorner_, double *uppercorner_); //constructor
  ~RootNode(); //destructor

  double lowercorner[numdimen]; //Used to store the lower corner values of the node, the limits of the simulation box
  double uppercorner[numdimen]; //Used to store the upper corner values of the node, the limits of the simulation box


  //double mass;    /**< mass of the particles in the node */
  //double com[numdimen];

  //double GetUpperEdge(int k) const;
  //double GetLowerEdge(int k) const;

  Node *children[numchildren]; //Array of pointers to the children nodes

  /*Method to pass particle to children nodes*/
  void PassParticle(Particle_vector_element_pointer pass_particle);
 
 private:
  double *lowercorntemp;  //Temporary pointer used to pass the lower corner values to the node
  double *uppercorntemp;  //Temporary pointer used to pass the upper corner values to the node
  Node_Type whatami;  //What type of node is the node (ROOT, since this is the root node)
  double x_halfway;  //The x-midpoint of the node
  double y_halfway;  //The y-midpoint of the node
  //double z_halfway;  //The z-midpoint of the node (currently off for development)

  /*Method to create a child node*/
  Node *BearChild(quad_octant_name quad_octant);

  /*Method to figure out which quadrant/octant a particle belongs in*/
  quad_octant_name FigureQuadOctant(Particle particle_);

};

#endif //ROOTNODE_H_
