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
#include "global.h"


int main(int argc, char **argv)
{
  if(argc != 2) return -1;
  int N = atoi(argv[1]);
  
  double dt = .8e-3;
  
  double particlemass = 1.0;

  Particle_vector particles;

  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-10.0;
  lowercorner[1]=-10.0;
  uppercorner[0]=10.0;
  uppercorner[1]=10.0;

  for(int i=0; i<N; i++)
    {
      for(int j=0; j<N; j++)
        {
          double x = ( ((double)i+.5)/((double)(N))) * (uppercorner[0] - lowercorner[0]) + lowercorner[0];
          double y = ( ((double)j+.5)/((double)(N))) * (uppercorner[1] - lowercorner[1]) + lowercorner[1];
          particles.push_back(Particle(particlemass,x,y));
          particles.push_back(Particle(particlemass,x+40.,y));                    
        }
    }

  printf("%lu   %lf\n",particles.size(),theta);
  
  //particles.push_back(Particle(particlemass,.75,.75));

  //particles[12].x += 0.;
  //particles[12].y += .2;
  
  lowercorner[0]=-5000.0;
  lowercorner[1]=-5000.0;
  uppercorner[0]=5000.0;
  uppercorner[1]=5000.0;



  
  Force force;
  
  const std::string integrator_name = "leapfrog";

  Integrator *integrator = NULL;
  if (integrator_name.compare("euler") == 0) {
    //printf("#Setting up an euler integrator\n");
    integrator = new Euler(dt, force);
  } 
  else if (integrator_name.compare("leapfrog") == 0) {
    //printf("#Setting up a leapfrog integrator\n");
    integrator = new Leapfrog(dt, force);
  } 
  else if (integrator_name.compare("rk4") == 0) {
    //printf("#Setting up a runge-kutta integrator\n");
    integrator = new RungeKutta4(dt, force);
  }
  if (integrator == NULL) {
    fprintf(stderr, "ERROR: integrator %s is not known\n",
            integrator_name.c_str());
  }

  Node root(lowercorner,uppercorner,ROOT);
  double t = 0.;
  for(t=0.; t<dt*100; t+=dt)
    {

      for(int i=0; i<particles.size(); i++)
        {
          root.FigureParticle(&particles[i]);

        }
      
      Node_vector_element_pointer initnodes;
      initnodes.push_back(&root);
      integrator->step(t, particles, initnodes);
      
      root.Reset();
    }

  delete integrator;
  return 0;
}
