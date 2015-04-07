#ifndef NODE_H_
#define NODE_H_

#include "global.h"

class Node {
public:
  Node();
  Node(double mass, double* x);
  ~Node();

  Node_Type whatami;

  double mass;    /**< mass of the particles in the node */

  double x[numdimen];

  Node_pointer point; /*pointer to the next node in the tree*/

  /*methods*/
  void BearChildren();

};

typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
