OBJS    = main.o client.o menu.o
CXX     = g++
DEBUG   = -g
CXXFLAGS  = -Wall $(DEBUG) -std=c++11 -pthread
LDFLAGS = -pthread

client: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.o main
