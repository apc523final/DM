#include <cmath>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "particle.h"
#include "integrator.h"
#include "euler.h"
#include "force.h"
#include "runge-kutta.h"
#include "leapfrog.h"
#include "euler_semi_implicit.h"


int numerrors;

void checkerror_double(const double value_to_check, const double value_to_check_against, const char *error_name, int particle_num=-1)
{
  double epsilon = 1.e-15;
  if( fabs(value_to_check - value_to_check_against) > epsilon)
    {
      if(particle_num == -1) printf("ERROR DETECTED!!!!  Error name: %s\n",error_name);
      else  printf("ERROR DETECTED!!!!  Error name: %s, loop number:%d\n",error_name,particle_num);
      printf("You got %e, compared against %e\n",value_to_check,value_to_check_against);
      numerrors++;
    }
}

void checkerror_int(const int value_to_check, const int value_to_check_against, const char *error_name, int particle_num=-1)
{
  if( value_to_check != value_to_check_against)
    {
      if(particle_num == -1) printf("ERROR DETECTED!!!!  Error name: %s\n",error_name);
      else  printf("ERROR DETECTED!!!!  Error name: %s, loop number:%d\n",error_name,particle_num);
      printf("You got %d, compared against %d\n",value_to_check,value_to_check_against);
      numerrors++;
    }
}

void checkerror_double2(const double value_to_check, const double value_to_check_against, const char *error_name, int particle_num=-1)
{
  double epsilon = 1.e-6;
  if( fabs(value_to_check - value_to_check_against) > epsilon)
    {
      if(particle_num == -1) printf("ERROR DETECTED!!!!  Error name: %s\n",error_name);
      else  printf("ERROR DETECTED!!!!  Error name: %s, loop number:%d\n",error_name,particle_num);
      printf("You got %.10lf, compared against %.10lf\n",value_to_check,value_to_check_against);
      numerrors++;
    }
}



int main()
{
  numerrors = 0;

  double dt = .00001;
  
  Particle_vector particles;
  particles.push_back(Particle(1.0,-.5,.5));
  particles.push_back(Particle(1.0,.5,.5));

  particles[0].vy = 1./sqrt(2.);
  particles[1].vy = -1./sqrt(2.);

  double omega = sqrt(2);//sqrt(G*(1.+1.)/1.);

  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-1.0;
  lowercorner[1]=-1.0;
  uppercorner[0]=1.0;
  uppercorner[1]=1.0;

  


  
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

  for(int i=0; i<4; i++)
    {
      checkerror_int(root.children[i]->whatami,EMPTY,"Empty initial error");
      checkerror_double(root.children[i]->mass,0.,"Empty initial error mass");
      checkerror_double(root.children[i]->com[0],0.,"Empty initial error com x");
      checkerror_double(root.children[i]->com[1],0.,"Empty initial error com y");
    }


  for(int i=0; i<particles.size(); i++)
    {
      root.FigureParticle(&particles[i]);
    }

  for(int i=0; i<2; i++)
    {
      checkerror_int(root.children[i]->whatami,LEAF,"Whatami Error Initial",i);
      checkerror_double(root.children[i]->mass,particles[i].mass,"Mass Error Initial",i);
      checkerror_double(root.children[i]->com[0],particles[i].x,"X Position Error Initial",i);
      checkerror_double(root.children[i]->com[1],particles[i].y,"Y Position Error Initial",i);
    }

  checkerror_int(root.children[SE]->whatami,EMPTY,"Empty error");
  checkerror_int(root.children[SW]->whatami,EMPTY,"Empty error");

  root.Reset();

  checkerror_double(root.mass,0.,"reset root mass problem");
  checkerror_double(root.com[0],0.,"reset root center of mass x problem");
  checkerror_double(root.com[1],0.,"reset root center of mass y problem");

  for(int i=0; i<4; i++)
    {
      checkerror_int(root.children[i]->whatami,EMPTY,"Empty reset error");
      checkerror_double(root.children[i]->mass,0.,"Empty reset error mass");
      checkerror_double(root.children[i]->com[0],0.,"Empty reset error com x");
      checkerror_double(root.children[i]->com[1],0.,"Empty reset error com y");
    }


  //check force
  Node_vector_element_pointer initnodes;
  initnodes.push_back(&root);

  int z=0;

  for(double t=0.; t<dt*50000; t+=dt)
    {
      checkerror_double2(particles[0].x,.5*sin(omega*t - M_PI/2.0),"particle 1 x position",z);
      checkerror_double2(particles[0].y,.5*sin(omega*t) + .5,"particle 1 y position",z);
      checkerror_double2(particles[1].x,.5*cos(omega*t),"particle 2 x position",z);
      checkerror_double2(particles[1].y,-.5*sin(omega*t) + .5,"particle 2 y position",z);
      
      for(int i=0; i<particles.size(); i++)
        {
          root.FigureParticle(&particles[i]);
        }

      
      Node_vector_element_pointer initnodes;
      initnodes.push_back(&root);
      integrator->step(t, particles, initnodes);
      
      
      if(numerrors !=0)
        {
          break;
        }

      
      root.Reset();
      z++;
    }
  
  printf("*********\n Total number of errors: %d\n********\n",numerrors);
  
  return 0;
}
