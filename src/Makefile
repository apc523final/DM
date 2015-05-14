INCDIR=-I.
LIBDIR=
testdir=./tests
CFLAGS=-Wall -O3 -g -std=c++0x $(INCDIR) $(LIBDIR)
CXX=g++

.PHONY: clean

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

all: basicsim basicersim

tests: test testforce

basicsim: basicsim.o node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^

basicersim: basicersim.o node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^

test: $(addprefix $(testdir)/, test.main.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o
	$(CXX) $(CFLAGS) -o $@ $^

testforce: $(addprefix $(testdir)/, test.force.o) node.o particle.o euler.o force.o runge-kutta.o leapfrog.o euler_semi_implicit.o
	$(CXX) $(CFLAGS) -o $@ $^


clean:
	-rm -rf *.o tests/*.o basicsim basicersim tests/test tests/testforce
