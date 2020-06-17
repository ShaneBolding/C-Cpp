#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstddef> 
#include <cstring>  
#include <sys/types.h> 
#include <unistd.h>
#include <time.h>
#include <thread>
#include <mutex>          // std::mutex

#include "param.hpp"
#include "parser.hpp"

#define BUFFER_SIZE 1024

//g++ -std=c++11 -pthread Untitled1.cpp 
//with threads: Time taken by program is : 100.000000 sec

using namespace std;
mutex mtx;
long int N;
bool LOCK = true;

void foo(long int *N, unsigned long int a[]) //mechanism to lock the global variables
{
	
	long int temp,temp2,i;
	if(LOCK)
	{	
		mtx.lock();
	}
	temp2 = *N;
	*N = *N - 1;
	if(LOCK)
	{	
		mtx.unlock();
	}
	temp = temp2;
	while(temp2>0)
	{
		i = 0;
		while(temp>0)
		{
			if(temp==1)
			{
				break;
			}
			if(temp%2 == 0)
			{
				temp = temp/2;
				//printf("even: %li %li\n",temp,temp2);
			}
			else 
			{
				temp = (3 * temp) + 1;
				//printf("odd: %li %li\n",temp,temp2);
			}
			i++;
		}
		
		
		if(LOCK)
		{	
			mtx.lock();
		}
		if(i<1000)
		{
			a[i] += 1;
		}
		temp2 = *N;
		*N = *N - 1;
		if(LOCK)
		{	
			mtx.unlock();
		}
		
		temp = temp2;
	}

	
}



int main(int argc, char** argv) 
{	
	Parser myParser; //parses user input
	Param* param; 	 //gets parse and reads it as a parameter

	// store user input
	char input[BUFFER_SIZE];
	

	if(argc==1)
	{
		string line;
		string buffer = "buffer ";
		getline(cin,line);
		strcpy(input,buffer.c_str());
		strcat(input, line.c_str());
	}
	
	
	//enables the program to put the argv in one string
	if(argc>1)
	{
		int i = 0;
		//strcpy(input,argv[0]);
		strcpy(input,argv[0]);
		for(i=0;i<argc;i++)
		{
			strcat(input,argv[i]);
			strcat(input," ");
		}
	}
	else cout<<"Invalide Parameters"<<endl; //if there arent exactly 3 parameters
	

	//checks input
	if (strlen(input) == 0) {
		cout << "Give Valid Commands!!!" << endl; //invalid (e.g. words where numbers are expected)
		return 0;
	}
		
	//constructing param
	param = myParser.parse(input);
		
	//checking if param is valid
	if (param ==NULL) {
		cout << "invalid input" << endl;
	}
	
	int T; //threads
	N = param->getNumber(); //number of calculations
	T = param->getThreads();
	LOCK = param->isLock();
	unsigned long int a[1000] = {};
	thread *threads = new thread[T];
	
	struct timespec ts1; // both C11 and POSIX
    clock_gettime(CLOCK_REALTIME, &ts1); // POSIX


	for (int j = 0; j < T; j++)
	{
		threads[j] = thread(foo,&N,a);
		//cout << threads[j].get_id() << endl;
	}
	for (int j = 0; j < T; j++) 
	{
		threads[j].join();
	}
		
	param->printParams();
		
	struct timespec ts2;
    clock_gettime(CLOCK_REALTIME, &ts2);
    double posix_dur = 1000.0*ts2.tv_sec + 1e-6*ts2.tv_nsec - (1000.0*ts1.tv_sec + 1e-6*ts1.tv_nsec);
	printf("%f\n", posix_dur); //CPU time in miliseconds using REALTIME

	//printf("%lu, %i, %d\n", N, T, posix_dur);
	/*for(int i = 0;i<500;i++)
	{
		cerr<<a[i]<<endl;
	}*/
	
	return 0;
}
