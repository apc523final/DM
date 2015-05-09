/* Header file for the force calculation code*/


#ifndef FORCE_H_
#define FORCE_H_

#include <vector>
#include "global.h"
#include "particle.h"
#include "node.h"


/*Define functions used in Force calculation*/

float calculateforce(Particle p1);
float findseparation(Particle p1, Particle p2);




#endif //FORCE_H_
