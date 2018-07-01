# DM

This is a gravitational tree code, useful for solving the gravitational N-body problem for a large number of particles. Rather than 
directly calculating the forces betweens all pairs of particles, which is O(N^2), tree codes aggregate particles and use an aggregate mass
for calculations with a greater than specified separation between particles.

This was written by Kris Pardo and Joshua Wallace as a final project for Princeton University's APC 523 course, "Numerical Algorithms for 
Scientific Computing."

The name "DM" is a reference to dark matter, one of the mysterious components of the universe that we know little about other than that it 
likes clumping together and exerts a gravitational force.  In simulations, dark matter is usually treated as a bunch of particles,
and tree codes or other approximate algorithms are usually necessary to tractably simulate the large number of dark matter particles needed 
for a realistic simulation.


## Directories
  src - where the source code is
      src/tests - where our test codes are stored
      src/basicsims - some of the basic simulations we created to test our code
          Note: see README in each of these directories for more information
  visualization - code implementing vispy to visualize the output

PLEASE NOTE THE FOLLOWING:
Our code requires C++11 compiler such as clang version>=3.3 or gcc
version>=4.6

Github repo of the code can be found at
https://github.com/apc523final/DM.git

## Example Code

An example code that runs a very basic simulation can be found in src/example.main.cc.
All the essential elements of a workable simulation can be found there.  We refer
interested persons to that example script.  It can be compiled
(in the src directory) with

make example

## Visualization Code

A simulation which prints out the positions of the particles using the
print_particles() function (written in particle.{cc,h}) with a newline
after every time step can be visualized movie-style with the Python
script in the visualization/ directory.  If these particle positions 
were outputted to a file named 'output.txt', the following command

python vis.py output.txt

if vispy is installed, will provide a visualization of the particle 
positions given in output.txt.  Vispy can be installed at 
https://github.com/vispy/vispy.

Script credit: [Semyeong Oh](https://github.com/smoh), adapted for our purposes.

