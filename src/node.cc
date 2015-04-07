#include "node.h"

Node::Node()

  for(int i=0; i<numchildren; i++)
    {
      children.push_back(NULL);
    }


BearChild(quad_octant_name quad_octant)
{

  if(ndimen == 2)
    {
      double lowercorner_temp[2];
      double uppercorner_temp[2];
      switch(quad_octant)
        {
        case NW:
          lowercorner_temp[0] = 
        case NE:
        case SE:
        case SW:
        }



  return Node(mass, x, lowercorner, uppercorner);
}
