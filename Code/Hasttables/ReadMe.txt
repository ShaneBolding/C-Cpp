Shane Bolding
Data Structures and Algorithms II
Project 1
User's Manual

Setup and Compilation
1.Download and unzip boldings-p1.zip from elearning to a Linux box in the multi-platform lab.
2.The zip file should contain:
	*dictionary.c
	*dictionary.h
	*file.c
	*file.h
	*password.c
	*password.h
	*main.c
	*lastNames.txt
	*makefile
	*ReadMe.txt
	*FunctionalDecomposition.txt
3.Enviroment: This project should work on the multi-platform lab.
4.Compiling: The makefile listed above should compile everything if you
type make. This should make an runnable program named run.

Running the project. Make sure in the same directory the .txt file
lastNames is present. No user input is needed.

User input: no users are need to run this program.

Output: all output should be shown in the console and should look like:

name from rawData.dat: smith
password before encryption: xoo1ouyt5
password encrypted: 1tu4sz51e
password from hashtable: 1tu4sz51e
false password before encryption: xooaouyt5
false password encrypted: 1tudsz51e

The next lines will be of the names at the 10000th, 20000th, ..., 80000th spot.
	