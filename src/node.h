#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"


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

  double mass;    /**< mass of the particles in the node */
  double com[numdimen];
    
 
 private:
  //std::vector<Node *> children(4); /*pointer to the child nodes*/
  Node *children[4];

  Node *BearChild(quad_octant_name quad_octant);

   
};

//typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
