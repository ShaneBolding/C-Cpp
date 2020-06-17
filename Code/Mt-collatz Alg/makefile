OBJS    = mt-collatz.o param.o parser.o
CXX     = g++
DEBUG   = -g
CXXFLAGS  = -Wall $(DEBUG) -std=c++11 -pthread
LDFLAGS = -pthread

mt-collatz: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.o mt-collatz
	