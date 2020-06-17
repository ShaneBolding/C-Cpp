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

#include "user.hpp"
#include "parser.hpp"
#include "multiServer.hpp"
#define BUFFER_SIZE 1024

//g++ -std=c++11 -pthread Untitled1.cpp 
//with threads: Time taken by program is : 100.000000 sec

using namespace std;


int main(int argc, char** argv) 
{	
	
	server(argc,argv);
	//menu();
	//Parser* parser = new Parser();
	//parser->registerUser("shane","123456");
	//parser->checkLoginInfo("shane","123456"); 			####IMPLEMENTED IN MENU
	//parser->registerUser("XxSniperKillerxX","8560");   		####IMPLEMENTED IN MENU
	//parser->registerUser("DUDEBRO","8560");			####
	//parser->changePassword("XxSniperKillerxX","8560","7895");	####IMPLEMENTED IN MENU
	//parser->deleteUser("XxSniperKillerxX","8560"); 		####
	//parser->banUser("DUDEBRO","8560");				####
	//parser->chatHistory("godwashere","DoodleBob");		//	####	
	
	return 0;
}
