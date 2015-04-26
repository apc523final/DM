#include <stdio.h>
#include "rootnode.h"
#include "node.h"
#include "particle.h"

RootNode::RootNode(double *lowercorner_, double *uppercorner_)
  :  lowercorntemp(lowercorner_),
     uppercorntemp(uppercorner_),
     whatami(ROOT)

{
  lowercorner[0] = lowercorntemp[0];
  lowercorner[1] = lowercorntemp[1];
  uppercorner[0] = uppercorntemp[0];
  uppercorner[1] = uppercorntemp[1];

  x_halfway = lowercorner[0] + (uppercorner[0] - lowercorner[0])/2.0;
  y_halfway = lowercorner[1] + (uppercorner[1] - lowercorner[1])/2.0;

  children[NW] = BearChild(NW);
  children[NE] = BearChild(NE);
  children[SE] = BearChild(SE);
  children[SW] = BearChild(SW);
  
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

quad_octant_name RootNode::FigureQuadOctant(Particle particle)
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

Node *RootNode::BearChild(quad_octant_name quad_octant)
{
  //printf("Root node bearing child, quadrant %d\n", quad_octant);
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
          //case uNW:
          //case uNE:
          //case uSW:
          //case uSE:
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

  return new Node(quad_octant, lowercorner_temp, uppercorner_temp, EMPTY);
    }
}

double RootNode::GetUpperEdge(int k) const
{
  if(k>=numdimen)
    {
      printf("Trying to access an edge value greater than the number of dimensions: %d\n",k);
      return 0.0;
    }
  else
    {
      return this->uppercorner[k];
    }
}

double RootNode::GetLowerEdge(int k) const
{
  if(k>=numdimen)
    {
      printf("Trying to access an edge value greater than the number of dimensions: %d\n",k);
      return 0.0;
    }
  else
    {
      return this->lowercorner[k];
    }
}

void RootNode::PassParticle(Particle_vector_element_pointer pass_particle)
{
  if(whatami == ROOT)
    {
      //printf("Root passing particle, with mass %e\n",pass_particle.mass);
      quad_octant_name q_o;
      q_o = FigureQuadOctant(*pass_particle);
      printf("      ###passing particle going to quadrant %d\n",q_o);
      children[q_o]->FigureParticle(pass_particle);
    }
  else
    {
      printf("What is going on?  I am supposed to be the ROOT node, but I am not.  I am the %d node\n",whatami);
    }
}

RootNode::~RootNode()

{
  //Delete children
  for(int i=0; i<numchildren; i++)
    {
      delete children[i];
    }
}

