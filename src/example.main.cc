#include <cmath>
/*This is an example code, showing the basic parts that need to be put 
  together for the code to work.*/

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "node.h"
#include "particle.h"
#include "integrator.h"
#include "euler.h"
#include "force.h"
#include "runge-kutta.h"
#include "leapfrog.h"
#include "euler_semi_implicit.h"


int main()
{
  //Define a time step size
  double dt = 1.e-3;
  
  //Define a Particle_vector, here named particles, in which to store the particles of the simulation
  Particle_vector particles;

  //Add particles to the Particle_vector
  double particlemass = 1.;
  particles.push_back(Particle(particlemass,1.,1.));
  particles.push_back(Particle(particlemass,-1.,-1.));

  //Define the lower and upper corners of the simulation box
  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-5.0;
  lowercorner[1]=-5.0;
  uppercorner[0]=5.0;
  uppercorner[1]=5.0;

  
  //Create a Force type, here named force
  Force force;

  //Here choose the integration scheme:
  //a string named integrator_name is used to store the
  //choice of integration scheme
  const std::string integrator_name = "rk4";

  //and then an Integrator is set up based on the selected integration scheme
  Integrator *integrator = NULL;
  if (integrator_name.compare("euler") == 0) {
    printf("#Setting up an euler integrator\n");
    integrator = new Euler(dt, force);
  } 
  else if (integrator_name.compare("leapfrog") == 0) {
    printf("#Setting up a leapfrog integrator\n");
    integrator = new Leapfrog(dt, force);
  } 
  else if (integrator_name.compare("rk4") == 0) {
    printf("#Setting up a runge-kutta integrator\n");
    integrator = new RungeKutta4(dt, force);
    }
  else if (integrator_name.compare("euler semi") == 0) {
    printf("#Setting up an euler-semi-implicit integrator\n");
    integrator = new Euler_SI(dt, force);
  }
  if (integrator == NULL) {
    fprintf(stderr, "ERROR: integrator %s is not known\n",
            integrator_name.c_str());
  }


  //Create a root node
  Node root(lowercorner,uppercorner,ROOT);

  //Create a variable to track the time
  double t = 0.;

  //Loop for a chosen amount of time
  for(t=0.; t<dt*100; t+=dt)
    {
      //Put the particles all in their appropriate
      //place in the tree structure
      for(int i=0; i<particles.size(); i++)
        {
          root.FigureParticle(&particles[i]);
        }

      //Define a Node_vector_element_pointer, used in the force calculation
      Node_vector_element_pointer initnodes;

      //Put the root node into this Node_vector_element_pointer
      initnodes.push_back(&root);

      //Step the integrator
      integrator->step(t, particles, initnodes);

      //Print the particle locations and/or energies
      //The setup below currently just prints to stdout
      //print_particles prints the x,y,z coordinates of each particle
      //in a horizontal line as follows:  x1  y1  z1  x2  y2  z2 ...
      print_particles(particles, std::cout);
      //prints total energy of all particles
      printf(" %e ",total_energy(particles));
      printf("\n");

      //Reset the tree structure
      root.Reset();
    }

  return 0;
}
