//Libraries
#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//External Files
#include "parser.hpp"
//#include "param.cpp"

Parser::Parser(){}
using namespace std;
/*function to parse and tokenize the input from the user */


Param* Parser::parse(char* input) {
	
	
	// if no input 
	if (input == NULL) {
		return NULL;
	}
	//tokenize
	char* token = strtok(input, " \t\n");
	if (token == NULL) {
		return NULL;
	}
	// begin constructing param object
	Param* param = new Param();
	int i = 0;
	while (token != NULL) {
		if(i==1)
		{
			param->setNumber(atol(token));	
		}
		if(i==2)
		{
			param->setThreads(atoi(token));
		}
		if(strcmp(token,"[-nolock]")==0) {
			param->setNolock();	
		}
		//Put token in argV
		param->addArgument(token);
		// get next token
		token = strtok (NULL, " \t\n");
		i++;
    }
	return param; //return parameter to main.cpp
}
