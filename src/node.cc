#include <stdio.h>
#include "node.h"
#include "particle.h"

//Creator of Node
Node::Node(double *lowercorner_, double *uppercorner_, Node_Type nodetype)
  :  //quad_octant_(quad_octant), //Set what quadrant/octant of the parent node this node belongs to.
     lowercorntemp(lowercorner_), //Temporary pointer used to pass the lower corner values to the node
     uppercorntemp(uppercorner_), //Temporary pointer used to pass the upper corner values to the node
     whatami(nodetype) //What type of node is the node: PARENT, LEAF, EMPTY, ROOT

{
  lowercorner[0] = lowercorntemp[0]; //Set x-coordinate of the lower corner
  lowercorner[1] = lowercorntemp[1]; //Set y-coordinate of the lower corner
  uppercorner[0] = uppercorntemp[0]; //Set x-coordinate of the upper corner
  uppercorner[1] = uppercorntemp[1]; //Set y-coordinate of the upper corner
  
  x_halfway = lowercorner[0] + (uppercorner[0] - lowercorner[0])/2.0; //The x-midpoint of the node
  y_halfway = lowercorner[1] + (uppercorner[1] - lowercorner[1])/2.0; //The y-midpoint of the node
  //z_halfway = lowercorner[2] + (uppercorner[2] - lowercorner[2])/2.0;  //The z-midpoint of the node (currently off for development)

  /*If this is the ROOT node, start out with some children already*/
  if(nodetype == ROOT)
    {
      children[NW] = BearChild(NW); //Create the NW child
      children[NE] = BearChild(NE); //Create the NE child
      children[SE] = BearChild(SE); //Create the SE child
      children[SW] = BearChild(SW); //Create the SW child
    }
  
  /*If not root node, nitialize all the pointers to children to be NULL; we haven't had any children yet!*/
  else
    {
      for(int i=0; i<numchildren; i++)
        {
          children[i] = NULL;
        }
    }
}

//Create a child node
Node *Node::BearChild(quad_octant_name quad_octant)
{
  if(numdimen == 2) //If we have two dimensions
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
      return new Node(lowercorner_temp, uppercorner_temp, EMPTY);
    }
}

//Figure out which quadrant/octant a particle will belong to
quad_octant_name Node::FigureQuadOctant(Particle particle)
{
  if(numdimen == 2) //If the number of dimensions is 2
    {
      //If the particle is outside the boundaries of the box
      if(particle.x < lowercorner[0] || particle.x > uppercorner[0] || particle.y < lowercorner[1] || particle.y > uppercorner[1])
          {
            printf("#Particle is outside the boundaries of the node, don't know what to do with it.\n");
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

//Figure out what to do with the particle that has been passed to me
void Node::FigureParticle(Particle_vector_element_pointer passed_particle)
{
  if(whatami == ROOT)  //Should be a root node, so enter this part of the statement
    {
      quad_octant_name q_o;  //quadrant/octant for the particle being passed
      q_o = FigureQuadOctant(*passed_particle);  //Figure out which quadrant/octant the particle belongs to
      if(q_o != ERROR_)  //Put it in the tree
        {
          children[q_o]->FigureParticle(passed_particle);  //Pass particle to that quadrant/octant
        }
      //Else we received an error for the quad/octant.  The particle, for instance, may be outside the simulation box
      //it won't be included in the tree anywhere
    }
  
  else if(whatami == PARENT) //If I already have children nodes
    {
      quad_octant_name qo;
      qo = FigureQuadOctant(*passed_particle); //Figure the quadrant the passed particle belongs in
      
      if(children[qo] == NULL) //If this quadrant has no child yet
        {
          children[qo] = BearChild(qo);  //Create the child node
        }
      UpdateCOM(*passed_particle); //Update the center of mass
      children[qo]->FigureParticle(passed_particle); //Pass the particle to this child node
    }  
  else if(whatami == LEAF) //If I have a particle but no children
    {
      quad_octant_name qo;
      qo = FigureQuadOctant(*passed_particle);  //Figure the quadrant the passed particle belongs in
      
      UpdateCOM(*passed_particle); //Update center of mass
      
      children[qo] = BearChild(qo);  //Create the child node
      children[qo]->FigureParticle(passed_particle);  //Pass the particle to the child node
      
      quad_octant_name qo2;
      qo2 = FigureQuadOctant(*particle_leaf);  //Figure quadrant of particle already contained in this leaf node

      if(qo == qo2)
        {
          children[qo]->FigureParticle(particle_leaf);  //Pass the particle to the child node, which already exists
        }
      else
        {
          children[qo2] = BearChild(qo2);  //Create the child node
          children[qo2]->FigureParticle(particle_leaf); //Pass the particle (already contained in this leaf) to the child node
        }
      particle_leaf = NULL;  //Remove this node's attachment to a specific particle
      whatami = PARENT;  //This node is now a parent node
    }
  else if(whatami == EMPTY) //If the node is EMPTY
    {
      mass = passed_particle->mass; //Update node mass to be particle mass
      com[0] = passed_particle->x;  //Update center of mass position to be particle position
      com[1] = passed_particle->y;  //Update center of mass position to be particle position
      /*if(numdimen == 3)
        {
        com[2] = passed_particle.z;  //Update center of mass position to be particle position
        }*/
      particle_leaf = passed_particle;  //Attach this particle to this node
      whatami = LEAF;  //Node is now a LEAF node
    }  
}

//Update center of mass of all particles contained in this node and its children
void Node::UpdateCOM(Particle passed_particle)
{
  double weighted_x = mass*com[0] + passed_particle.mass * passed_particle.x;
  com[0] = weighted_x / (mass + passed_particle.mass);
  double weighted_y = mass*com[1] + passed_particle.mass * passed_particle.y;
  com[1] = weighted_y / (mass + passed_particle.mass);
  /*if(numdimen == 3)
    {
      double weighted_z = mass*com[2] + passed_particle.mass * passed_particle.z;
      com[2] = weighted_z / (mass + passed_particle.mass);
      }*/
  mass += passed_particle.mass;
}

void Node::Reset()
{
  if(whatami == ROOT)
    {
      for(int i=0; i<numchildren; i++)
        {
          delete children[i];
        }
      children[NW] = BearChild(NW); //Create the NW child
      children[NE] = BearChild(NE); //Create the NE child
      children[SE] = BearChild(SE); //Create the SE child
      children[SW] = BearChild(SW); //Create the SW child

      mass = 0.;
      for(int i=0; i<numdimen; i++)
        {
          com[i] = 0.;
        }
    }
  else
    {
      printf("Only the ROOT node can reset! Error!\n");
    }
}
      

//Destructor
Node::~Node()  
{
  //Delete children nodes
  for(int i=0; i<numchildren; i++)
    {
      if(whatami != LEAF)
        {
          if(children[i] != NULL)
            {
              delete children[i];
            }
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
