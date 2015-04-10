#include "node.h"
#include "stdio.h"

Node::Node(quad_octant_name quad_octant, double *lowercorner, double *uppercorner, Node_Type nodetype)
  :  quad_octant_(quad_octant),
     lowercorntemp(lowercorner),
     uppercorntemp(uppercorner),
     whatami(nodetype)

{
  lowercorner_[0] = lowercorner[0];
  lowercorner_[1] = lowercorner[1];
  uppercorner_[0] = uppercorner[0];
  uppercorner_[1] = uppercorner[1];

  x_halfway = lowercorner_[0] + (uppercorner_[0] - lowercorner_[0])/2.0;
  y_halfway = lowercorner_[1] + (uppercorner_[1] - lowercorner_[1])/2.0;

  //children.resize(numchildren);
  /*if(numdimen == 3)
    {
      lowercorner_[2] = lowercorner_[2];
      uppercorner_[2] = uppercorner_[2];
      }*/
    
  /*for(int i=0; i<numchildren; i++)
    {
      children.push_back(Node);
      }*/
  
}

/*if(numdimen==2)
  {
    x_halfway = Node.lowercorner_[0] + (Node.uppercorner_[0] - Node.lowercorner_[0])/2.0;
    y_halfway = lowercorner_[1] + (uppercorner_[1] - lowercorner_[1])/2.0;
  }
 else if(numdimen==3)
   {
     x_halfway = lowercorner_[0] + (uppercorner_[0] - lowercorner_[0])/2.0;
     y_halfway = lowercorner_[1] + (uppercorner_[1] - lowercorner_[1])/2.0;
     z_halfway = lowercorner_[2] + (uppercorner_[2] - lowercorner_[2])/2.0;
     }*/


Node Node::BearChild(quad_octant_name quad_octant)
{

  if(numdimen == 2)
    {
      double lowercorner_temp[2];
      double uppercorner_temp[2];
      switch(quad_octant)
        {
        case NW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = uppercorner_[1];
        case NE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = uppercorner_[1];
        case SE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = lowercorner_[1];
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = y_halfway;
        case SW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = lowercorner_[1];
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = y_halfway;
        case lNW:
        case lNE:
        case lSW:
        case lSE:
          printf("Shouldn't be here\n");
        }

  return Node(quad_octant, lowercorner_temp, uppercorner_temp, LEAF);
    }
}

  /*else if(ndimen == 3)
    {
      double lowercorner_temp[3];
      double uppercorner_temp[3];
      switch(quad_octant)
        {
        case lNW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = y_halfway;
          lowercorner_temp[2] = lowercorner_[2];
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = uppercorner_[1];
          uppercorner_temp[2] = z_halfway;
        case lNE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = y_halfway;
          lowercorner_temp[2] = lowercorner_[2];
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = uppercorner_[1];
          uppercorner_temp[2] = z_halfway;
        case lSE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = lowercorner_[1];
          lowercorner_temp[2] = lowercorner_[2];
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = y_halfway;
          uppercorner_temp[2] = z_halfway;
        case lSW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = lowercorner_[1];
          lowercorner_temp[2] = lowercorner_[2];
          uppercorner_temp[0] = x_halway;
          uppercorner_temp[1] = y_halfway;
          uppercorner_temp[2] = z_halfway;

        case uNW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = y_halfway;
          lowercorner_temp[2] = z_halfway;
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = uppercorner_[1];
          uppercorner_temp[2] = uppercorner_[2];
        case uNE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = y_halfway;
          lowercorner_temp[2] = z_halfway;
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = uppercorner_[1];
          uppercorner_temp[2] = uppercorner_[2];
        case uSE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = lowercorner_[1];
          lowercorner_temp[2] = z_halfway;
          uppercorner_temp[0] = uppercorner_[0];
          uppercorner_temp[1] = y_halfway;
          uppercorner_temp[2] = uppercorner_[2];
        case uSW:
          lowercorner_temp[0] = lowercorner_[0];
          lowercorner_temp[1] = lowercorner_[1];
          lowercorner_temp[2] = z_halfway;
          uppercorner_temp[0] = x_halway;
          uppercorner_temp[1] = y_halfway;
          uppercorner_temp[2] = uppercorner_[2];
          }*/
