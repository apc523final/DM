INCDIR=
LIBDIR=
CFLAGS=-Wall -O3 -g -std=c++0x $(INCDIR) $(LIBDIR)
CXX=g++

.PHONY: clean

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^



test: test.main.o node.o particle.o euler.o force.o 
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o test
