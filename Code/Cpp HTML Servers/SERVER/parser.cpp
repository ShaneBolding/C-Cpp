//Libraries
#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fstream>
#include <iomanip>

//External Files
#include "parser.hpp"
//#include "user.cpp"

/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**4/5/2020
**COP4635 Project 2
**
*/


/****************************
**Function: Parser file which parses file I/O and helps
**compare .txt files with User objects.
**
*/

using namespace std;

Parser::Parser(){}



User* Parser::checkLoginInfo(char* username, char* password) {
	
	ifstream fp("dataBase.txt");
	//fp.open();
	char buff2[255];
	
	// if no input 
	if ((username == NULL)||(password == NULL)){
		return NULL;
	}

	//tokenize
	string buffer;
	if(!fp.is_open())
	{
		return NULL;
	}

	char* token;
	int i = 0;
	while (getline(fp,buffer)) {
		
		strcpy(buff2,buffer.c_str());
		//checks username
		if(i%3==0)
		{
			token = strtok(buff2, "\t\n");
			if(!strcmp(token,username))
			{
				cout<<"\tUSER FOUND"<<endl;
				User* user = new User();
				user->setUsername(username);
				token = strtok(NULL, " \t\n");
				if(!strcmp(token,password))
				{
					cout<<"\tPASSWORDS MATCH"<<endl;
					user->setPassword(password);
				}
				else
				{
					cout<< "\tWrong password try again" <<endl;
					delete user;
					fp.close();
					return NULL;
				}
				char* token = strtok(NULL, " \t\n");
				if(token[0]=='A')
				{
					cout<<"\tWELCOME ADMIN"<<endl;
					user->setAdmin(true);
				}
				else if(token[0]=='B')
				{
					cout<<"\tYou Are BANNED"<<endl;
					user->setAdmin(false);
				}
				else 
				{
					cout<<"\tWELCOME USER"<<endl;
					user->setAdmin(false);
				}
				user->setAccountNumber(atoi(&token[1]));

				fp.close();
				user->printUser();
				return user; //username and password match return User class.
			}
			else	//if username does not match the username it progresses to the next one.
			{
			
				token = strtok(buff2, " \t\n");
				token = strtok(buff2, " \t\n");
				i += 3;
			
			}
			
		}
	}
	cout<< "\tUser not found" <<endl;
	fp.close();
	return NULL; //if code gets here that means the user does not exist in the database.

}

User* Parser::registerUser(char* username, char* password) {
	
	
	ifstream fp("dataBase.txt");
	//fp.open();
	char buff2[255];
	
	// if no input 
	if ((username == NULL)||(password == NULL)){
		return NULL;
	}
	
	//tokenize
	string buffer;
	if(!fp.is_open())
	{
		return NULL;
	}

	char* token;
	int i = 0;
	while (getline(fp,buffer)) {
		
		strcpy(buff2,buffer.c_str());
		//checks username
		if(i%3==0)
		{
			token = strtok(buff2, "\t\n");
			if(!strcmp(token,username))
			{
				cout<< "\tUsername has been taken" <<endl;
				fp.close();
				return NULL; //Username exists therefore return NULL and let user try again
			}
			else	//if username does not match the username it progresses to the next one.
			{
			
				token = strtok(NULL, " \t\n");
				token = strtok(NULL, " \t\n");
				i += 3;
			
			}
			
		}
	}
	fp.close();
	ofstream out("dataBase.txt", std::ios_base::app);
	//username is not taken therefore create and populate User class.
	User* user = new User();
	user->setUsername(username);
	/* TO DO IF password checker if the password needs to have certain characters */
	user->setPassword(password);
	user->setAdmin(false);
	/* TO DO add random number generator */
	user->setAccountNumber(456785);	//random account number for now
	out << username << "\t" << password << "\t" << "x" << "456785" << endl;
	out.close();
	return user;
}

bool Parser::deleteUser(char* username, char* password)
{
	
	string line;
	string badUsername = string(username);
	string badPassword = string(password);
	string full = badUsername + "\t" + badPassword;
	int i = 0;
	ifstream myfile;
	myfile.open("dataBase.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (getline(myfile, line))
	{
		//if the line does not match that means
		//username and password do not match
		//copy to temp file
		if (line.substr(0,full.size()) != full)
		{
			temp << line << endl;
		}
		else
		{
			i++;
		}
	}
	
	myfile.close();
	temp.close();
	remove("dataBase.txt");
	rename("temp.txt", "dataBase.txt");
	if(i==1)
	{
		cout << "\tThe user with the name " << badUsername << " has been deleted." << endl;
		return true;	
	}
	else return false;
	
	
}

bool Parser::changePassword(char* username, char* oldPassword, char* newPassword) 
{
	
	
	bool deletion = this->deleteUser(username,oldPassword);
	if(deletion == false)
	{
		return false;
	}
	else
	{
		this->registerUser(username,newPassword);
		return true;
	}
	
}

bool Parser::banUser(char* username)
{
	string line;
	string badUsername = string(username);
	string badPassword = "XXXXX";
	
	string full = badUsername + "\t" + badPassword;
	string bannedUser = badUsername + "\t" + badPassword + "\t" + "B666";
	int i = 0;
	ifstream myfile;
	myfile.open("dataBase.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (getline(myfile, line))
	{
		//if the line does not match that means
		//username and password do not match
		//copy to temp file
		if (line.substr(0,full.size()) != full)
		{
			temp << line << endl;
		}
		else
		{
			temp << bannedUser << endl;
			i++;
		}
	}
	
	myfile.close();
	temp.close();
	remove("dataBase.txt");
	rename("temp.txt", "dataBase.txt");
	if(i==1)
	{
		cout << "\tThe user with the name " << badUsername << " has been banned." << endl;
		return true;	
	}
	else return false;
}


void Parser::chatHistory(char* firstUser, char* secondUser)
{
	
	string line;
	string fileName;
	string first = string(firstUser);
	string second = string(secondUser);
	//returns 1 is firstUser is alphabetically less than second
	if(bool(firstUser<secondUser)==0)
	{
		fileName = first+second+".txt";
	}
	else fileName = second+first+".txt";
	if(fileName.size()==0)
	{
		return;
	}
	
	ifstream myfile;
	myfile.open(fileName);
	if(!myfile.is_open())
	{
		cout << "\tNo chat history\n";
		return;
	}
	ofstream temp;
	while (getline(myfile, line))
	{
		cout<<line<<endl;	
	}
	
	myfile.close();
	return;
	
}

