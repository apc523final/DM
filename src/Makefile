INCDIR=
LIBDIR=
CFLAGS=-Wall -O3 -std=c++0x $(INCDIR) $(LIBDIR)
CXX=g++

.PHONY: clean

%.o: %.cc
	$(CXX) -c $(CFLAGS) -o $@ $^

test: test.main.o node.o particle.o  
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	-rm -rf *.o test
