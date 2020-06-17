#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>

#include "param.hpp"

using namespace std;
/*functions for getting the parameters from the tokenizing process in parser.cpp*/
/*CONSTRUCTORS*/
Param::Param()
{
	_number = 0;
	_threads = 0;
	_argumentCount = 0;
	_nolock = false;
} 

Param::Param (long int N, int threads)
{
		_number = N;
		_threads = threads;	
		_argumentCount = 0;
}

/*SETTERS*/

void Param::setNumber (long int N)
{
	_number = N;
}

void Param::setThreads (int T)
{
	_threads = T;
}
 
void Param::addArgument(char *argument)
{
   	  _argumentVector[_argumentCount++] = argument;
}

void Param::setNolock(void)
{
   	  _nolock = true;
}

/*DEBUGGING*/
void Param::printParams()    
{ 

	//cout<< "ArgumentCount: [" << _argumentCount << "]" << endl;
			for (int i = 1; i < 3 ; i++)
				cout  << _argumentVector[i] << endl;
}

/*GETTERS*/

long int Param::getNumber (void)
{
	return _number;
}
int Param::getThreads (void)
{
	return _threads;
}

char* Param::getArgument(int i)
{
	if (i < _argumentCount && i >= 0) {
		return _argumentVector[i];
	} else {
		return NULL;
	}
}

char** Param::getArgV(void)
{
	return _argumentVector;
}

/*PRINTERS*/

/*FLAGS*/
bool Param::isLock(void)
{
	if(_nolock)
	{
		return false;
	}
	return true;
}



