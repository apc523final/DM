#include <cmath>
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
  //numchildren = 4;

  double dt = 1e-7;
  int numx = 2;
  int numy = 2;
  double particlemass = 100.0;
  
  Particle_vector particles;



  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-5.0;
  lowercorner[1]=-5.0;
  uppercorner[0]=5.0;
  uppercorner[1]=5.0;

  for(int i=0; i<numx; i++)
    {
      for(int j=0; j<numy; j++)
        {
          double x = ( ((double)i+.5)/((double)(numx + 1))) * (uppercorner[0] - lowercorner[0]) + lowercorner[0];
          double y = ( ((double)j+.5)/((double)(numy + 1))) * (uppercorner[1] - lowercorner[1]) + lowercorner[1];
          particles.push_back(Particle(particlemass,x,y));;
        }
    }
  
  Force force;
  
  const std::string integrator_name = "euler semi";

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

  Node root(lowercorner,uppercorner,ROOT);
  double t = 0.;
  int z = 0;
<<<<<<< HEAD
  for(t=0.; t<dt*12000; t+=dt)
=======
  for(t=0.; t<dt*1e7; t+=dt)
>>>>>>> 7164d55213fd2381666645359c6ea6a4f2f27414
    {

      for(int i=0; i<particles.size(); i++)
        {
          root.FigureParticle(&particles[i]);

        }
      
      Node_vector_element_pointer initnodes;
      initnodes.push_back(&root);
      integrator->step(t, particles, initnodes);
      

      root.Reset();
      

       if(z%20 == 0)
         {
           print_particles(particles, std::cout);
         }      
      z++;
    }

  return 0;
}
