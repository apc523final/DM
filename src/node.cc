#ifndef NODE_H_
#define NODE_H_

class Node {
 public:
  Node();
  Node(double mass, double x, double y, double z);
  ~Node();

  double mass;    /**< mass of the particles in the node */

  double x;  /**< center of mass position x */
  double y;  /**< center of mass position y */
  double z;  /**< center of mass position z */

  bool root;  /*
  Node_pointer point; /*pointer to the next node in the tree*/

};

typedef std::vector<Node> Node_pointer;

#endif //NODE_H_
