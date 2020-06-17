#ifndef USER_
#define USER_

class User { 
  private:    
  	std::string _username;
  	char* _password;    
  	bool  _admin;                   /* admin identifier        */      
  	int _accountNumber;           /* account number for the user */  
  	long int _portNumber;
  	bool _inGroupChat;
  	char* _privateChat;
	    
	
	
  public: 
   //CONSTRUCTORS///////////////////////////////////////////////////
   User();
   User(char* username, char* password, char admin, int accountNumber);
   
   //SETTERS////////////////////////////////////////////////////////
   void setUsername (char *username);
   void setPassword(char *password);
   void setAdmin(bool admin);
   void setAccountNumber(int accountNumber);
   void setPortNumber(long int portNumber);
   void	setGroupChat(bool GC);
   void setPrivateChat(char* recieverName);

   //DEBUGGING//////////////////////////////////////////////////////
   void printUser();
   
   //GETTERS////////////////////////////////////////////////////////
   char* getUsername();
   char* getPassword();
   bool  getAdmin();
   long int getPortNumber();
   bool	 getGroupChat();
   char* getPrivateChat();
   
   //PRINTERS///////////////////////////////////////////////////////
   void  printFile();
   void  printDir();
   void  grep();
   
   //FLAGS//////////////////////////////////////////////////////////
   
};

#endif
