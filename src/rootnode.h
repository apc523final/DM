#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"


class RootNode {
 public:
  //Node();
  RootNode(double *lowercorner, double *uppercorner);
  ~RootNode();

  double *lowercorntemp;
  double *uppercorntemp;
  Node_Type whatami;
  double lowercorner_[numdimen];
  double uppercorner_[numdimen];

  double x_halfway;
  double y_halfway;

  double mass;    /**< mass of the particles in the node */
  double com[numdimen];
    
 
 private:
  //std::vector<Node *> children(4); /*pointer to the child nodes*/
  Node *children[4];

  Node BearChild(quad_octant_name quad_octant);

};

#endif //NODE_H_
