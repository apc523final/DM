#include <stdio.h>
#include "node.h"
#include "particle.h"

Node::Node(quad_octant_name quad_octant, double *lowercorner_, double *uppercorner_, Node_Type nodetype)
  :  quad_octant_(quad_octant),
     lowercorntemp(lowercorner_),
     uppercorntemp(uppercorner_),
     whatami(nodetype)

{
  lowercorner[0] = lowercorntemp[0];
  lowercorner[1] = lowercorntemp[1];
  uppercorner[0] = uppercorntemp[0];
  uppercorner[1] = uppercorntemp[1];
  
  x_halfway = lowercorner[0] + (uppercorner[0] - lowercorner[0])/2.0;
  y_halfway = lowercorner[1] + (uppercorner[1] - lowercorner[1])/2.0;
  
  
  for(int i=0; i<numchildren; i++)
    {
      children[i] = NULL;
    }
}
  
Node *Node::BearChild(quad_octant_name quad_octant)
{
  
  if(numdimen == 2)
    {
      double lowercorner_temp[2];
      double uppercorner_temp[2];
      switch(quad_octant)
        {
        case NW:
          lowercorner_temp[0] = lowercorner[0];
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = uppercorner[1];
          break;
        case NE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = uppercorner[0];
          uppercorner_temp[1] = uppercorner[1];
          break;
        case SE:
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = lowercorner[1];
          uppercorner_temp[0] = uppercorner[0];
          uppercorner_temp[1] = y_halfway;
          break;
        case SW:
          lowercorner_temp[0] = lowercorner[0];
          lowercorner_temp[1] = lowercorner[1];
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = y_halfway;
          break;
        case lNW:
        case lNE:
        case lSW:
        case lSE:
          printf("Shouldn't be here\n");
          break;
        case ROOT_:
          printf("Seriously?!?\n");
          break;
        case ERROR_:
          printf("I got an erroneous quadrant value...\n");
          break;
        }
      
      return new Node(quad_octant, lowercorner_temp, uppercorner_temp, LEAF);
    }
}

quad_octant_name Node::FigureQuadOctant(Particle particle)
{
  if(numdimen == 2)
    {
      if(particle.x < lowercorner[0] || particle.x > uppercorner[0] || particle.y < lowercorner[1] || particle.y > uppercorner[1])
          {
            printf("Particle is outside the boundaries of the root node, don't know what to do with it.\n");
            return ERROR_;
          }
      
      if(particle.x < x_halfway)
        {
          if(particle.y < y_halfway)
            {
              return SW;
            }
          else
            {
              return NW;
            }
        }
      else
        {
          if(particle.y < y_halfway)
            {
              return SE;
            }
          else
            {
              return NE;
            }
        }
    }
  else if(numdimen == 3)
    {
      printf("Not programmed yet, 3 dimensions for FigureQuadOctant");
      return ERROR_;
    }
  else
    {
      printf("Don't know what to do with this number of dimensions: %d\n",numdimen);
      return ERROR_;
    }
}

void Node::FigureParticle(Particle passed_particle)
{
  printf("Here\n");
}

Node::~Node()
  
{
  //Delete children nodes
  for(int i=0; i<numchildren; i++)
    {
      if(children[i] != NULL)
        {
          delete children[i];
        }
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
