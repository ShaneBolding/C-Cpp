run : main.o password.o file.o dictionary.o
	gcc main.o password.o file.o dictionary.o -o run.exe
	
dictionary.o : dictionary.c dictionary.h
	gcc -c -Wall dictionary.c
	
password.o : password.c password.h
	gcc -c -Wall password.c
	
file.o : file.c file.h password.h dictionary.h
	gcc -c -Wall file.c

main.o : main.c file.h dictionary.h
	gcc -c -Wall main.c

clean :
	rm *.o run rawData.dat encryptedData.txt
	
rem :
	rm *.dat