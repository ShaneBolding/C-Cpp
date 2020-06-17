OBJS    = lizard.o
CXX     = g++
DEBUG   = -g
CXXFLAGS  = -Wall $(DEBUG) -std=c++11 -pthread
LDFLAGS = -pthread

lizard: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.o lizard
	