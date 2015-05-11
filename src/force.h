/* Header file for the force calculation code*/


#ifndef FORCE_H_
#define FORCE_H_

#include <vector>
#include "global.h"
#include "particle.h"
#include "node.h"


/*Define functions used in Force calculation*/



class Force {
 public:
  Force(int gravity=1);
  ~Force();

  void calculateforce(Node_vector &nodes, Particle_vector &particles);
  double calculateseparation(Particle &p, Node &n);

 private:
  int gravity_;
};


#endif //FORCE_H_
