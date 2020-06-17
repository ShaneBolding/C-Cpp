#ifndef MENU
#define MENU

#define USIZE 20  //Username Size
#define PSIZE 8   //password size


void clrscrn();
void menu();
void registerUser();
char* stringCat(char request[2],char username[USIZE], char passwrod[PSIZE]);
void loginUser();
void clientMenu(int sockfd,char* username, int admin);
void displayUsers(int sockfd);
void groupChat(int sockfd,char* username);
void privateChat(int sockfd,char* username);
void pullHistory(char* username);
void FTP();
void passwordRequest(int sockfd,char* username);
bool verifyAdmin(char* username);

#endif
