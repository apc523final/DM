#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "global.h"

class Node {
 public:
  //Node();
  Node(double mass, double *x, double *lowercorner, double *uppercorner);
  ~Node();

  double *lowercorntemp;
  double *uppercorntemp;
  double lowercorner_[numdimen];
  double uppercorner_[numdimen];

  double mass;    /**< mass of the particles in the node */
  double com[numdimen];
    
  Node_Type whatami;

 private:
  Node_pointer children; /*pointer to the child nodes*/
  
  Node *BearChild(quad_octant_name quad_octant);

   
};

typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
