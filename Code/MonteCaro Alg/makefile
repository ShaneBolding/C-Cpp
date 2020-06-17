run : main.o sim.o equations.o
	gcc main.o sim.o equations.o -lm -o run
	
equations.o : equations.c equations.h
	gcc -c -Wall equations.c
	
sim.o : sim.c sim.h equations.h 
	gcc -c -Wall sim.c

main.o : main.c sim.h 
	gcc -c -Wall main.c

clean :
	rm *.o run 
