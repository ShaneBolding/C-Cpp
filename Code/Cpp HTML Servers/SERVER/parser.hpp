#ifndef PARSER_
#define PARSER_

#include "user.hpp"

class Parser{

	public:
		Parser();
		
		User* checkLoginInfo(char* username, char* password);
		User* registerUser(char* username, char* password);
		bool  deleteUser(char* username, char* password);
		bool  changePassword(char* username, char* oldPassword, char* newPassword);
		bool  banUser(char* username);
		void  chatHistory(char* firstUser, char* secondUser);
		
};

#endif
