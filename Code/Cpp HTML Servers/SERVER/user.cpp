#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>

#include "user.hpp"

using namespace std;
/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**4/5/2020
**COP4635 Project 2
**
*/


/****************************
**Function: User class file for getting setting 
**and using the object user.
**
*/

//CONSTRUCTORS///////////////////////////////////////////////////////////////////////////////////
User::User()
{
	_username = "\n";
	_password = NULL;
	_admin = false; // no background processing
	_accountNumber = 0;
	_portNumber = 0;
	_inGroupChat = false;
	_privateChat = NULL;
		
} 

User::User(char* username, char* password, char admin, int accountNumber)
{
		_username = std::string(username);
		_password = password;
		if(admin == 'A')
		{
			_admin = true;
		}else _admin = false;
		_accountNumber = accountNumber;
}

//SETTERS/////////////////////////////////////////////////////////////////////////////////////////
void User::setUsername (char *username)
{
	cout << "maybe I should use easy print statements" << endl;
	_username = std::string(username);
	cout<<"is this the problem of course it is \n";
}
  
void User::setPassword(char *password)
{
	_password = password;
}

void User::setAdmin(bool admin)
{
	_admin = admin;
}

void User::setAccountNumber(int accountNumber)
{
	_accountNumber = accountNumber;
}

void User::setPortNumber(long int portNumber)
{
	_portNumber = portNumber;
}

void User::setGroupChat(bool GC)
{
	_inGroupChat = GC;
}

void User::setPrivateChat(char* recieverName)
{
	_privateChat = recieverName;
}

//DEBUGGING////////////////////////////////////////////////////////////////////////////////////////
void User::printUser()    
{ 
	cout << "\tusername: [" << _username << "]" << endl <<         
			"\tpassword: [" << ((_password != NULL) ? _password : "NULL") << "]" << endl <<         
 			"\taccountNumber: [" << ((_accountNumber != 0) ? _accountNumber : 0) << "]" << endl <<
 			"\tadmin: [" << ((_admin != 0) ? "True" : "False") << "]" << endl; 
}

//GETTERS////////////////////////////////////////////////////////////////////////////////////////
char* User::getUsername()
{
	char* tmp;
	strcpy(tmp, _username.c_str());
	return tmp;
}

char* User::getPassword()
{
	return _password;
}

bool User::getAdmin()
{
	return _admin;
}

long int User::getPortNumber()
{
	return _portNumber;
}

bool User::getGroupChat()
{
	return _inGroupChat;
}

char* User::getPrivateChat()
{
	return _privateChat;
}

//PRINTERS///////////////////////////////////////////////////////////////////////////////////////
void User::printFile()
{
	/*
	if(_argumentVector[1] == NULL)
	{
		return;
	}
	if(_argumentVector[1][0] == '<')
	{
		ifstream f(_username);
		if(f.is_open())
		{
			cout<<f.rdbuf();
		}
		return;
	}
	else 
	{
		ifstream f(_argumentVector[1]);
		if(f.is_open())
		{
			cout<<f.rdbuf();
		}
		return;
	}
	return;
	//prints out file until it reaches the end
	
	*/

}

void User::printDir()
{
	/*
	DIR*    dir;
	dirent* pdir;
	char* files[255];

	if(_argumentCount >= 3 && _argumentVector[2][0]== '>')
	{
		dir = opendir(".");
		int i = 0;
		FILE *fp;
		fp = fopen(_password,"w");
		while (pdir = readdir(dir)) 
		{
		    //files[i] = pdir->d_name;
		    fprintf(fp,pdir->d_name);
		    fprintf(fp,"\n");
		    i++;
		}
		fclose(fp);
	}
	else
	{	
		dir = opendir(".");
		int i = 0;
		while (pdir = readdir(dir)) 
		{
			
		    files[i] = pdir->d_name;
		    if(i%5==0 && i!=0)
		    {
		    	cout<<endl;
		    }
		    cout<<files[i]<<"\t";
		    i++;
		}
		cout<<endl;
	}
	*/
}

void User::grep()
{
	/*
	ifstream fp (_argumentVector[3]);
	string buffer;
	char buff2[255];
	if(fp == NULL)
	{
		cout<<"file can't be opened"<<endl;
		return;
	}
	else
	{
		while(getline(fp,buffer))
		{
			strcpy(buff2,buffer.c_str());
			char* token = strtok(buff2, " \t\n");

			if (token == NULL) {
				return;
			}
			while (token != NULL) 
			{
	
				if(strcmp(token,_argumentVector[2])==0)
			    {
			    	cout<<buffer<<endl;
				}
				// get next token
				token = strtok (NULL, " \t\n");
				
		    }
		}
	}
	*/
}

//FLAGS//////////////////////////////////////////////////////////////////////////////////////////



