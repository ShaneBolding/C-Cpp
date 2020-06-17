#ifndef SERVER
#define SERVER
/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**2/16/2020
**COP4635 Project 1
**
**TCP HTTP server
*/
int setupConn();
//void setHttpHeader(char httpHeader[],char *filePath,int func);
void getHtml(char htmlPage[],char* filePath,int func);

void serv(int sockfd);

void sendFile(int nsockfd,char *filePath);

#endif
