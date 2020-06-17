//libraries
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "menu.hpp"
#include "client.hpp"


/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**4/5/2020
**COP4635 Project 2
**
*/


/****************************
**Function: Menu file. This file shows the client/user
**options for the client/user to pick. Based on these
**options this file calls the appropriate function.
**
*/

using namespace std;
void clrscrn()
{
	cout << "\033[2J\033[1;1H";
	cout << "\n\n\n";
	cout << "\tChat Client\n";
	cout << "\tUser: " << "\n";
	cout << "\tStatus -- \n\n\n\n\n";
	cout << "\t++++++++++++++++++++++++++++++++++++++++++\n";

}


void menu()
{
	char option;
	while (option != '0')
	{
		clrscrn();
		cout << "\tMenu\n";
		cout << "\t++++++++++++++++++++++++++++++++++++++++++\n";
		cout << "\t1.Login\n";
		cout << "\t2.Register\n";
		cout << "\n";
		cout << "\n";
		cout << "\t0.Exit\n";
		cout << "\t====================================\n\n";
		cout << "\tEnter your selection: ";
		cin >> option;
		//cout << endl;
		switch (option)
		{
			case '1':
				//cout << "\n";
				//cout << "\n";
				loginUser();
				break;
			case '2':
				//cout << "\n";
				//cout << "\n";
				registerUser();
				break;
			case '0':
				cout << "\n\n\tExiting Chat Client\n";
				exit(1);
				
			default: cout <<option << "is not a valid menu item.\n";
				cout << endl;
		}
		
	}
	
}

char* stringCat(char request[2], char username[USIZE],char password[PSIZE])
{
	char loginfo[MAX];
	char* ptr = loginfo;
	
	strcpy(loginfo,request);
	strcat(loginfo, "%");
	strcat(loginfo,username);
	strcat(loginfo,"%");
	strcat(loginfo,password);
	strcat(loginfo,"%");

	return ptr;	
}


void loginUser()
{
	//call login here
	//call server with L0+USERNAME+PASSWORD+		
	
	clrscrn();
	char username[USIZE];
	char password[PSIZE];
	int userType;
	//char * usern;	
	int sockfd;	
	char loginInfo[MAX];
	//User* user;
	
	sockfd = connectToServer();

	cout << "\tLogin\n";
	cout << "\t++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\tEnter Username: ";
	cin >> username;
	clrscrn();
	cout << "\tEnter Password: ";
	cin >> password;
	strcpy(loginInfo ,stringCat("L0",username,password));
	/*
	strcpy(loginfo,"L0");
	strcat(loginfo,"%");
	strcat(loginfo,username);
	strcat(loginfo,"%");
	strcat(loginfo,password);
	strcat(loginfo,"%");
	*/

	//cout << loginfo << endl;
	
	userType = serv(sockfd, loginInfo);
	
	//cout << "MENU USERTYPE "<<userType << endl;

	//getchar();
	//getchar();

	//send(sd,loginfo,sizeof(loginfo));
	getchar();
	if (userType == 9)
	{
		clrscrn();
		cout << "\tLogin Failed\n";
		cout << "\tPress Enter To Continue\n\t";
		do 
		{	
			clrscrn();
			cout << "\tLogin Failed\n";
			cout << "\tPress Enter To Continue";
			getchar();
		}while(cin.get() != '\n');
		loginUser();
		
	}
	else
	{
		clrscrn();
		cout <<"\tLOGIN Success\n";
		clientMenu(sockfd, username, userType);
	}	
	
	
}



void registerUser()
{
	//call regiter info here
	//register R0+USERNAME+PASSWORD+
	clrscrn();
	char username[USIZE];
	char password[PSIZE];
	int userStatus;
	//char * usern;	
	int sockfd;	
	char loginInfo[MAX];
	//User* user;
		
	sockfd = connectToServer();


	cout << "\tRegister User\n";
	cout << "\tEnter Username: ";
	cin >> username;
	clrscrn();
	cout << "\tEnter Password: ";
	cin >> password;
	
	strcpy(loginInfo ,stringCat("R0",username,password));
	
	userStatus = serv(sockfd, loginInfo);
	getchar();
	if (userStatus == 1)
	{
		clrscrn();
		cout << "\tUser Registered\n\n";
		cout << "\tPress Enter To Login";
		do 
		{	
			clrscrn();
			cout << "\tPress Enter To Login";
			getchar();
		}while(cin.get() != '\n');
		
		loginUser();
		
	}
	else
	{
		clrscrn();
		cout <<"\tREGISTRATION FAILED\n";
		menu();
	}	
}




void clientMenu(int sockfd, char* username, int admin)
{

	
	char option;
		while(option != 9)
		{
			clrscrn();
			cout << "\tClient Menu\n";
			cout << "\t++++++++++++++++++++++++++++++++++++++++++\n";
			cout << "\t1. View Current Members Online\n"; //C0+
			cout << "\t2. Enter Group Chat\n"; //C1+
			cout << "\t3. Enter a private Chat\n"; //C2+
			cout << "\t4. View your chat History\n"; //H0+
			cout << "\t5. File Transfer to a user\n"; //F0+
			cout << "\t6. Change Password\n"; //P0+
			cout << "\t7. Logout\n"; //L0+
			if (admin == true)
			{
				cout << "\t8. Admin\n";//A0+
			}
			cout << "\t0. Return to login\n";
			cout << "\t====================================\n";
			cout << "\tEnter your selection: ";
			cin >> option;
			cout << endl;
			switch (option)
			{
				case '1':
					cout << "\tCurrent Members\n\n";
					displayUsers(sockfd);
					break;
				case '2':
					cout << "\tGroup Chat\n\n";
					groupChat(sockfd,username);
					break;				
				case '3':
					cout << "\tPrivate Chat\n\n";
					privateChat(sockfd,username);
					break;
				case '4':
					cout << "\tChat History\n\n";
					pullHistory(username);
					break;
				case '5':
					cout << "\tFile Transfer\n\n";
					FTP();
					break;
				case '6':
					cout << "\tChange Password\n";
					passwordRequest(sockfd,username);
					break;
				case '7':
					cout << "\tLogout\n";
					loginUser();	
					break;
				case '8':
	
					if (admin == true)
					{
						cout << "\tAdministrator\n";
						verifyAdmin(username);
						break;
					}
					else
						cout <<option << " is not a valid Selection\n";
					break;
				case '0':
					cout << "\tLogin\n";
					menu();
					break;
					
				default: cout <<option << " is not a valid Selection\n";
					cout << endl;
			}

		}

}



void displayUsers(int sockfd)
{
	int stat;	
	clrscrn();
	cout << "\t________________________\n";
	cout << "\tCurrent Users in Chat\n\n";
	
	cout << "\tYour Mom\n";
	cout << "\tUser 1\n";
	cout << "\tUser 2\n";
	cout << "\t________________________\n";
	getchar();
	stat = serv(sockfd,"C0%");
		
	getchar();
	getchar();
	/*
	if (cin.get() == '\n')
	{
		cout << "\tOutta\n\n";
	}
	*/

}

void groupChat(int sockfd,char* username)
{
	clrscrn();
	cout << "\t_________________________\n";
	cout << "\tWelcome to Group Chat\n";
	cout << "\n\n\n";
	
	chat(sockfd,username);
	/*
	if (cin.get() == '\n')
	{
		cout << "\tChatting \n\n\n";
	}
	*/
}

void privateChat(int sockfd,char* username)
{
	
	char chatName[MAX] = "C2%";

	clrscrn();
	cout << "\t_________________________\n";
	cout << "\tWelcome to Private Chat\n";
	cout << "\n\n\n";
	cout << "\tUsers here are:\n\n\n";
	getchar();	
	
	chat(sockfd, chatName);
	
	if (cin.get() == '\n')
	{
		cout << "\tStart Chat\n\n";
	}
}


void pullHistory(char* username)
{
	clrscrn();	
	cout << "\t_________________________\n";
	cout << "\tGetting Chat History\n\n";
	getchar();
	if (cin.get() == '\n')
	{
		cout << "\tNo History\n";
	}
}


void FTP()
{
	char option;
	char fileLoc[MAX];
	char userID[MAX];
	
	while (option != 9)
	{
	
		clrscrn();
		cout << "\t_________________________\n";
		cout << "\tFile Transfer\n\n";
		cout << "\t1. Select File to transfer:\n";
		cout << "\t2. Select User to transfer to:\n";
		cout << "\t0. Return\n";
		cout << "\t====================================\n";
		cout << "\tEnter your selection: ";
		
		cin >> option;
			switch(option)
			{
				case '1':
					clrscrn();
					cout << "\tEnter File Location as \n";
					cout << "\tfolder/location/of/file.example\n\n";
					cout << "\t====================================\n";
					cout << "\tFile Location: ";
					cin >> fileLoc;
					
					//enter file location
					break;
				case '2':
					clrscrn();
					cout << "\tTransfering file: " << fileLoc <<"\n\n";
					cout << "\tEnter User ID to transfer file to:\n";
					cout << "\t====================================\n";
					cout << "\tUser ID: ";
					
					cin >> userID;
					clrscrn();
					cout << "\tUser ID: " << userID;
					cout << "\n";
					cout << "\tTransfering: " << fileLoc;
					getchar();
					getchar();
					//transferFile(fileLoc,userID);//file.cpp
					break;
				case '0':
					return;
				default:
					cout << "\tnot a valid entry\n";
					break;
			}
	}
	
	clrscrn();
	cout << "\t_________________________\n";
	cout << "\tFile Transfer\n\n";
	getchar();
	if (cin.get() == '\n')
	{
		cout << "\tNo File\n";
	}

}


void passwordRequest(int sockfd,char* username)
{
	char oldPass[MAX];
	char newPass[MAX];
	char newPassConf[MAX];
	//bool changed;
	char loginInfo[MAX];
	int passStatus;
	//Parser* parser;
	clrscrn();	
	cout << "\t_________________________\n";
	cout << "\tEnter Old Password: ";
	cin >> oldPass;
	cout << "\n\n";
	do
	{
		clrscrn();
		cout << "\tEnter New Password: ";
		cin >> newPass;
		cout << "\n";
		cout << "\tConfirm New Password: ";
		cin >> newPassConf;
		if(strcmp(newPass,newPassConf) != 0)
		{
			clrscrn();
			cout << "\tPasswords Do Not Match:\n\tPlease Try again.\n";
			cout << "\tEnter to continue: ";
			getchar();
			getchar();
		}
	}while (strcmp(newPass,newPassConf)!=0);
	
	cout << "\tPasswords Match\n";	
	strcat(oldPass,"%");
	strcat(oldPass,newPass);
	//strcat(oldPass,"%");
		
	strcpy(loginInfo ,stringCat("P0",username,oldPass));
	
	passStatus = serv(sockfd, loginInfo);

	cout << oldPass << endl;
	getchar();
	if (passStatus == 1)
	{
		do 
		{	
			clrscrn();
			cout << "\tPassword Changed\n\n";
			cout << "\tPress Enter To Login";
		}while(cin.get() != '\n');
		
		loginUser();
		
	}
	else
	{
		clrscrn();
		cout <<"\tPassword Change FAILED\n";
		menu();
	}	

}


bool verifyAdmin(char* username)
{
	//char admin;
	char option;
	char userID[USIZE];
	//clrscrn();	
	while (option != '9')
	{
	
		clrscrn();
		cout << "\t_________________________\n";
		cout << "\tAdministration Menu\n\n";
		cout << "\t1. Ban a member\n";
		cout << "\t2. Block a member\n";
		cout << "\t0. Return\n";
		cout << "\t====================================\n";
		cout << "\tEnter your selection: ";
		
		cin >> option;
		
		switch(option)
		{
			case '1':
			{
				clrscrn();
				cout << "\tEnter User ID to Ban \n";
				cout << "\t\n\n";
				cout << "\t====================================\n";
				cout << "\tUser ID: ";
				cin >> userID;
				do 
				{	
					clrscrn();	
					cout << "\t====================================\n";
					cout << "\tUser ID: [" << userID;
					cout << "] has been Banned\n";
					cout << "\tPress Enter To Return";
					getchar();
				}while(cin.get() != '\n');
				break;
			}
			case '2':
			{
				clrscrn();
				cout << "\tEnter User ID to block\n";
				cout << "\t====================================\n";
				cout << "\tUser ID: ";
				cin >> userID;	
				do 
				{	
					clrscrn();
					cout << "\t====================================\n";
					cout << "\tUser ID: [" << userID;
					cout << "] has been Blocked\n\n";
					cout << "\tPress Enter To Return";
					getchar();
				}while(cin.get() != '\n');			
				
				
				break;
			}
			case '0':
			{
				return NULL;
			}
			default:
			{
				cout << "\tnot a valid entry\n";
				break;
			}
		}
	}
	

}




