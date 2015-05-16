INCDIR=-I.
LIBDIR=
testdir=./tests
basicsimdir=./basicsims
CFLAGS=-Wall -O3 -g -std=c++0x $(INCDIR) $(LIBDIR)
CXX=g++

.PHONY: clean

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

all: basicsim basicersim

tests: test testforce

basicsim: $(addprefix $(basicsimdir)/, basicsim.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^

basicersim: $(addprefix $(basicsimdir)/, basicersim.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^

test: $(addprefix $(testdir)/, test.main.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o
	$(CXX) $(CFLAGS) -o $@ $^

testforce: $(addprefix $(testdir)/, test.force.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^


clean:
	-rm -rf *.o tests/*.o basicsims/*.o basicsim basicersim test testforce
