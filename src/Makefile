INCDIR=
LIBDIR=
CFLAGS=-Wall -O3 -g -std=c++0x $(INCDIR) $(LIBDIR)
CXX=g++

.PHONY: clean

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

all: test basicsim basicersim

test: test.main.o node.o particle.o euler.o force.o runge-kutta.o leapfrog.o
	$(CXX) $(CFLAGS) -o $@ $^

basicsim: basicsim.o node.o particle.o euler.o force.o runge-kutta.o leapfrog.o
	$(CXX) $(CFLAGS) -o $@ $^

basicersim: basicersim.o node.o particle.o euler.o force.o runge-kutta.o leapfrog.o
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o test
