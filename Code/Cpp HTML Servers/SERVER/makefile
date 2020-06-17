CFLAGS = -g -Wall 
GFLAGS = -c -Wall
CC = gcc
LIBS= -g

all: server client


objServer = serverMain.o multiServer.o parser.o user.o
objClient = clientMain.o client.o menu.o
TARGET1 = server
TARGET2 = client


server: $(objServer)
	$(CC) -o $(TARGET1) $(objServer) $(LIBS)

serverMain.o: serverMain.cpp user.hpp parser.hpp multiServer.hpp
	$(CC) $(CFLAGS) serverMain.cpp $(LIBS)

multiServer.o: multiServer.cpp multiServer.hpp parser.hpp user.hpp
	$(CC) $(CFLAGS) multiServer.cpp $(LIBS)

parser.o: parser.cpp server.hpp
	$(CC) $(CFLAGS) parser.cpp $(LIBS)

user.o: user.cpp user.hpp
	$(CC) $(CFLAGS) user.cpp $(LIBS)


client: $(objClient)
	$(CC) -o $(TARGET2) $(objClient) $(LIBS)

client.o: client.cpp client.hpp
	$(CC) $(CFLAGS) -c client.cpp

menu.o: menu.cpp menu.hpp client.hpp
	$(CC) $(CFLAGS) -c menu.cpp

.PHONY : clean
clean: 
	rm *.o 

