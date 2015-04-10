#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"


class Node {
 public:
  //Node();
  Node(quad_octant_name quad_octant, double *lowercorner, double *uppercorner, Node_Type nodetype);
  ~Node();

  double *lowercorntemp;
  double *uppercorntemp;
  double lowercorner_[numdimen];
  double uppercorner_[numdimen];

  double x_halfway;
  double y_halfway;

  double mass;    /**< mass of the particles in the node */
  double com[numdimen];
    
  Node_Type whatami;
  quad_octant_name quad_octant_;

 private:
  //std::vector<Node *> children(4); /*pointer to the child nodes*/
  Node *children[4];

  Node BearChild(quad_octant_name quad_octant);

   
};

//typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
