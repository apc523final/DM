#include <cmath>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "particle.h"
#include "integrator.h"
#include "euler.h"
#include "force.h"


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

void checknotnum_double(const double value_to_check, const double value_to_check_against, const char *error_name, int particle_num=-1)
{
  double epsilon = 1.e-15;
  if( fabs(value_to_check - value_to_check_against) < epsilon)
    {
      if(particle_num == -1) printf("ERROR DETECTED!!!!  Error name: %s\n",error_name);
      else  printf("ERROR DETECTED!!!!  Error name: %s, loop number:%d\n",error_name,particle_num);
      printf("You got %e, compared against %e\n",value_to_check,value_to_check_against);
      numerrors++;
    }
}


int main()
{
  //numchildren = 4;
  numerrors = 0;

  double dt = .1;
  
  Particle_vector particles;
  particles.push_back(Particle(1.0,-1.0,1.0));
  particles.push_back(Particle(1.0,1.0,1.0));
  particles.push_back(Particle(1.0,1.0,-1.0));
  particles.push_back(Particle(1.0,-1.0,-1.0));

  double lowercorner[2];
  double uppercorner[2];
  lowercorner[0]=-2.0;
  lowercorner[1]=-2.0;
  uppercorner[0]=2.0;
  uppercorner[1]=2.0;

  Force force;
  
  const std::string integrator_name = "euler";

  Integrator *integrator = NULL;
  if (integrator_name.compare("euler") == 0) {
    printf("#Setting up an euler integrator\n");
    integrator = new Euler(dt, force);
  } /*else if (integrator_name.compare("leapfrog") == 0) {
    std::cerr << "#Setting up a leapfrog integrator" << std::endl;
    integrator = new Leapfrog(dt, force);
  } else if (integrator_name.compare("rk4") == 0) {
    std::cerr << "#Setting up a runge-kutta integrator" << std::endl;
    integrator = new RungeKutta4(dt, force);
    }*/
  if (integrator == NULL) {
    fprintf(stderr, "ERROR: integrator %s is not known\n",
            integrator_name.c_str());
  }


  Node root(lowercorner,uppercorner,ROOT);
  //printf("Root limits: %lf %lf %lf %lf\n",root.lowercorner[0], root.lowercorner[1], root.uppercorner[0], root.uppercorner[1]);
  //printf("NW corner: %lf %lf %lf %lf\n",root.children[NW]->lowercorner[0],root.children[NW]->lowercorner[1],root.children[NW]->uppercorner[0],root.children[NE]->uppercorner[1]);
  //printf("NE corner: %lf %lf %lf %lf\n",root.children[NE]->lowercorner[0],root.children[NE]->lowercorner[1],root.children[NE]->uppercorner[0],root.children[NE]->uppercorner[1]);
  //printf("SE corner: %lf %lf %lf %lf\n",root.children[SE]->lowercorner[0],root.children[SE]->lowercorner[1],root.children[SE]->uppercorner[0],root.children[SE]->uppercorner[1]);
  //printf("SW corner: %lf %lf %lf %lf\n",root.children[SW]->lowercorner[0],root.children[SW]->lowercorner[1],root.children[SW]->uppercorner[0],root.children[SW]->uppercorner[1]);

  checkerror_double(root.lowercorner[0],lowercorner[0],"Root X Lower Corner");
  checkerror_double(root.lowercorner[1],lowercorner[1],"Root Y Lower Corner");
  checkerror_double(root.uppercorner[0],uppercorner[0],"Root X Upper Corner");
  checkerror_double(root.uppercorner[1],uppercorner[1],"Root Y Upper Corner");
  
  checkerror_double(root.children[NW]->lowercorner[0],lowercorner[0],"NW X Lower Corner");
  checkerror_double(root.children[NW]->lowercorner[1],(lowercorner[1] + uppercorner[1])/2.,"NW Y Lower Corner");
  checkerror_double(root.children[NW]->uppercorner[0],(lowercorner[0] + uppercorner[0])/2.,"NW X Upper Corner");
  checkerror_double(root.children[NW]->uppercorner[1],uppercorner[1],"NW Y Upper Corner");

  checkerror_double(root.children[NE]->lowercorner[0],(lowercorner[0] + uppercorner[0])/2.,"NE X Lower Corner");
  checkerror_double(root.children[NE]->lowercorner[1],(lowercorner[1] + uppercorner[1])/2.,"NE Y Lower Corner");
  checkerror_double(root.children[NE]->uppercorner[0],uppercorner[0],"NE X Upper Corner");
  checkerror_double(root.children[NE]->uppercorner[1],uppercorner[1],"NE Y Upper Corner");
  
  checkerror_double(root.children[SE]->lowercorner[0],(lowercorner[0] + uppercorner[0])/2.,"SE X Lower Corner");
  checkerror_double(root.children[SE]->lowercorner[1],lowercorner[1],"SE Y Lower Corner");
  checkerror_double(root.children[SE]->uppercorner[0],uppercorner[0],"SE X Upper Corner");
  checkerror_double(root.children[SE]->uppercorner[1],(lowercorner[1] + uppercorner[1])/2.,"SE Y Upper Corner");

  checkerror_double(root.children[SW]->lowercorner[0],lowercorner[0],"SW X Lower Corner");
  checkerror_double(root.children[SW]->lowercorner[1],lowercorner[1],"SW Y Lower Corner");
  checkerror_double(root.children[SW]->uppercorner[0],(lowercorner[0] + uppercorner[0])/2.,"SW X Upper Corner");
  checkerror_double(root.children[SW]->uppercorner[1],(lowercorner[1] + uppercorner[1])/2.,"SW Y Upper Corner");

  for(int i=0; i<particles.size(); i++)
    {
      root.FigureParticle(&particles[i]);
    }

  for(int i=0; i<4; i++)
    {
      //printf("%d, type: %d   mass: %lf   com_x: %lf   com_y: %lf   \n",i,root.children[i]->whatami,root.children[i]->mass,root.children[i]->com[0],root.children[i]->com[1]);
      checkerror_int(root.children[i]->whatami,LEAF,"Whatami Error Initial",i);
      checkerror_double(root.children[i]->mass,particles[i].mass,"Mass Error Initial",i);
      checkerror_double(root.children[i]->com[0],particles[i].x,"X Position Error Initial",i);
      checkerror_double(root.children[i]->com[1],particles[i].y,"Y Position Error Initial",i);

      //checkerror_double(root.children[i]->particle_leaf->x,particles[i].x,"X Position Error particle_leaf",i);
      //checkerror_double(root.children[i]->particle_leaf->y,particles[i].y,"Y Position Error particle_leaf",i);
    }

  double mass2 = 2.0;
  Particle particle5;
  particle5 = Particle(mass2,-1.5,1.5);
  particles.push_back(particle5);
  
  root.FigureParticle(&particles[4]);
  
  checkerror_int(root.children[NW]->whatami,PARENT,"Parent Error Initial");
  checkerror_double(root.children[NW]->children[NW]->mass,mass2,"Parent passing particle correctly");
  checkerror_double(root.children[NW]->children[NE]->mass,1.0,"Parent passing existing particle correctly");

  //check force
  Node_vector initnodes;
  initnodes.push_back(root);
  printf("here\n");
  force.updateacceleration(initnodes, particles);
  printf("there\n");
  double accx = particle5.ax;
  checknotnum_double(accx, 0, "Acceleration is zero");

  
  printf("*********\n Total number of errors: %d\n********\n",numerrors);
  return 0;
}
