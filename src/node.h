#ifndef NODE_H_
#define NODE_H_

#include "global.h"

class Node {
 public:
  Node();
  Node(double mass, double* x, double *lowercorner, double *uppercorner);
  ~Node();
  
  Node_Type whatami;

  double mass;    /**< mass of the particles in the node */

  double x[numdimen];

  Node_pointer children; /*pointer to the child nodes*/

 private:
   Node *BearChild(quad_octant_name quad_octant);

   
};

typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
