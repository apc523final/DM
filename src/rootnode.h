#ifndef ROOTNODE_H_
#define ROOTNODE_H_

#include <vector>
#include "global.h"
#include "node.h"


class RootNode {
 public:
  //RootNode();
  RootNode(double *lowercorner_, double *uppercorner_);
  ~RootNode();

  double lowercorner[numdimen];
  double uppercorner[numdimen];


  double mass;    /**< mass of the particles in the node */
  double com[numdimen];

  double GetUpperEdge(int k) const;
  double GetLowerEdge(int k) const;
    
 
 private:
  //std::vector<Node *> children(4); /*pointer to the child nodes*/
  double *lowercorntemp;
  double *uppercorntemp;
  Node_Type whatami;
  double x_halfway;
  double y_halfway;
  
  Node *children[numchildren];

  Node *BearChild(quad_octant_name quad_octant);

};

#endif //ROOTNODE_H_
