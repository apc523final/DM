#include <stdio.h>
#include "rootnode.h"
#include "node.h"
#include "particle.h"

RootNode::RootNode(double *lowercorner_, double *uppercorner_)
  :  lowercorntemp(lowercorner_), //Temporary pointer used to pass the lower corner values to the node
     uppercorntemp(uppercorner_), //Temporary pointer used to pass the upper corner values to the node
     whatami(ROOT) //This is a ROOT node

{
  lowercorner[0] = lowercorntemp[0]; //Set x-coordinate of the lower corner
  lowercorner[1] = lowercorntemp[1]; //Set y-coordinate of the lower corner
  uppercorner[0] = uppercorntemp[0]; //Set x-coordinate of the upper corner
  uppercorner[1] = uppercorntemp[1]; //Set y-coordinate of the upper corner

  x_halfway = lowercorner[0] + (uppercorner[0] - lowercorner[0])/2.0; //The x-midpoint of the node
  y_halfway = lowercorner[1] + (uppercorner[1] - lowercorner[1])/2.0; //The y-midpoint of the node
  //z_halfway = lowercorner[2] + (uppercorner[2] - lowercorner[2])/2.0;  //The z-midpoint of the node (currently off for development)

  children[NW] = BearChild(NW); //Create the NW child
  children[NE] = BearChild(NE); //Create the NE child
  children[SE] = BearChild(SE); //Create the SE child
  children[SW] = BearChild(SW); //Create the SW child
  
}

//Figure out which quadrant/octant a particle will belong to
quad_octant_name RootNode::FigureQuadOctant(Particle particle)
{
  if(numdimen == 2) //If the number of dimensions is 2
    {
      //If the particle is outside the boundaries of the box
      if(particle.x < lowercorner[0] || particle.x > uppercorner[0] || particle.y < lowercorner[1] || particle.y > uppercorner[1])
          {
            printf("Particle is outside the boundaries of the node, don't know what to do with it.\n");
            return ERROR_;
          }
      
      if(particle.x < x_halfway)
        {
          if(particle.y < y_halfway) //It's in the SW position
            {
              return SW;
            }
          else  //It's in the NW position
            {
              return NW;
            }
        }
      else
        {
          if(particle.y < y_halfway)  //It's in the SE position
            {
              return SE;
            }
          else  //It's in the NE position
            {
              return NE;
            }
        }
    }
  else if(numdimen == 3)  //If the number of dimensions is 3
    {
      printf("Not programmed yet, 3 dimensions for FigureQuadOctant");
      return ERROR_;
    }
  else  //Don't know what to do with this number of dimensions
    {
      printf("Don't know what to do with this number of dimensions: %d\n",numdimen);
      return ERROR_;
    }
}

//Create a child node
Node *RootNode::BearChild(quad_octant_name quad_octant)
{
  if(numdimen == 2) //If the number of dimensions is 2
    {
      double lowercorner_temp[2]; //Stores what will be the lower corner of the child node being created
      double uppercorner_temp[2]; //Stores what will be the upper corner of the child node being created
      switch(quad_octant)
        {
        case NW: //If the child node is a NW node, set the corners to these values
          lowercorner_temp[0] = lowercorner[0];
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = uppercorner[1];
          break;
        case NE: //If the child node is a NE node, set the corners to these values
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = y_halfway;
          uppercorner_temp[0] = uppercorner[0];
          uppercorner_temp[1] = uppercorner[1];
          break;
        case SE: //If the child node is a SE node, set the corners to these values
          lowercorner_temp[0] = x_halfway;
          lowercorner_temp[1] = lowercorner[1];
          uppercorner_temp[0] = uppercorner[0];
          uppercorner_temp[1] = y_halfway;
          break;
        case SW: //If the child node is a SW node, set the corners to these values
          lowercorner_temp[0] = lowercorner[0];
          lowercorner_temp[1] = lowercorner[1];
          uppercorner_temp[0] = x_halfway;
          uppercorner_temp[1] = y_halfway;
          break;
        case lNW:
        case lNE:
        case lSW:
        case lSE:
          printf("Shouldn't be here\n"); //If two dimensions, should have l/u octants
          break;
        case ROOT_:
          printf("Seriously?!?\n");
          break;
        case ERROR_:
          printf("I got an erroneous quadrant value...\n");
          break;
        }
      //Create the new child node and return pointer to this node
      return new Node(quad_octant, lowercorner_temp, uppercorner_temp, EMPTY);
    }
}

//Pass particle to one of the children nodes
void RootNode::PassParticle(Particle_vector_element_pointer pass_particle)
{
  if(whatami == ROOT)  //Should be a root node, so enter this part of the statement
    {
      quad_octant_name q_o;  //quadrant/octant for the particle being passed
      q_o = FigureQuadOctant(*pass_particle);  //Figure out which quadrant/octant the particle belongs to
      children[q_o]->FigureParticle(pass_particle);  //Pass particle to that quadrant/octant
    }
  else //Should be a root node, shouldn't get to this spot
    {
      printf("What is going on?  I am supposed to be the ROOT node, but I am not.  I am the %d node\n",whatami);
    }
}

//Destructor
RootNode::~RootNode()

{
  //Delete children
  for(int i=0; i<numchildren; i++)
    {
      delete children[i];
    }
}

/*double RootNode::GetUpperEdge(int k) const
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
    }*/


