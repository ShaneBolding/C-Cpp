#ifndef CLIENT
#define CLIENT

#define MAX 2048
#define SA struct sockaddr

void sendFile(int nsockfd,char *filePath);
void receiveFile(int sockfd,char buff[MAX]);
int connectToServer();
int serv (int sockfd, char* loginfo);
void chat(int sockfd, char* loginfo);
#endif
