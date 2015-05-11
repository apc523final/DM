/* Header file defining the node class, the basic tree structure for the tree code
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"
#include "particle.h"

/*The Node class*/
class Node {
 public:
  Node(double *lowercorner_, double *uppercorner_, Node_Type nodetype); //constructor
  ~Node(); //destructor

  //quad_octant_name quad_octant_; //What quadrant/octant the node is in its parent node
  double *lowercorntemp;  //Temporary pointer used to pass the lower corner values to the node
  double *uppercorntemp;  //Temporary pointer used to pass the upper corner values to the node
  Node_Type whatami;  //What type of node is the node: PARENT, LEAF, EMPTY, ROOT
  double lowercorner[numdimen]; //Used to store the lower corner values of the node, its physical location
  double uppercorner[numdimen]; //Used to store the upper corner values of the node, its physical location

  double x_halfway;  //The x-midpoint of the node
  double y_halfway;  //The y-midpoint of the node
  //double z_halfway;  //The z-midpoint of the node (currently off for development)

  Particle_vector_element_pointer particle_leaf;  //Pointer to the specific particle this node contains, if a LEAF node
  
  double mass;    //mass of ALL the particles in the node
  double com[numdimen];  //Center of mass of the node
  Node *children[numchildren];  //Array of pointers to the children nodes

  /*Method to figure out what to do with a particle passed to it:
   Should I keep it, pass it to another child, create a child to keep it?*/
  void FigureParticle(Particle_vector_element_pointer passed_particle);
 
 private:

  /*Method to create a child node*/
  Node *BearChild(quad_octant_name quad_octant);

  /*Method to figure out which quadrant/octant a particle belongs in*/
  quad_octant_name FigureQuadOctant(Particle particle_);

  /*Method to update the center of mass of a node, based on a passed particle*/
  void UpdateCOM(Particle passed_particle);

};

//Define a std::vector for storing many instances of Node
typedef std::vector<Node> Node_vector;

//Define a pointer to a specific element of Particle_vector
//This pointer is also (roughly?) equivalent to Particle *
typedef std::vector<Node>::pointer Node_vector_element_pointer;


#endif //NODE_H_
