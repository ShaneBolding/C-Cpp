#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>

#include "client.hpp"
/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**4/5/2020
**COP4635 Project 2
**
*/


/****************************
**Function: Client file that operates the connection with the 
**server through sockets.
**
*/

#define RSIZE 1025
#define MAXS 2048
#define PORT 60001 
#define SA struct sockaddr 

using namespace std;


/****************************
**Function sendFile
**Purpose write image file as bytes to HTML client
**Return N/A
**Input nsockfd <-socket connection.  filePath <-image file.
**
*/

void sendFile(int nsockfd,char *filePath)
{
	char imgHeader[] = "HTTP/1.1 200 OK\r\n"
			   //"Content-Type: image/gif\r\n"			  
			   //"Accept-Ranges: bytes\r\n"
			   "\r\n";

	send(nsockfd,imgHeader,sizeof(imgHeader)-1,0);
	printf("\n%s\n",imgHeader);
	
	FILE * pFile;
	long lSize;
	//char * buffer;
	//size_t result;
	
	printf("file path:%s\n\n",filePath);
	
	pFile = fopen (filePath+1 , "rb" );
	printf("file path:%s\n\n",filePath+1);
		
	if (pFile==NULL) 
	{
		fputs ("File error",stderr); 
		return;
	}

	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);


	printf("Sending Picture as Byte Array\n");
	char send_buffer[MAXS]; // no link between BUFSIZE and the file size
	int nb = fread(send_buffer, 1, sizeof(send_buffer), pFile);
	while(!feof(pFile)) 
	{
		//printf("PACKET:%s\n",send_buffer);
		write(nsockfd, send_buffer, nb);
		nb = fread(send_buffer, 1, sizeof(send_buffer), pFile);
	}
	fclose(pFile);
}






/****************************
**Function	receiveFile
**Purpose	If server sends file save data into txt document 
**Return 	N/A
**Input 	sockfd <-socket connection  buff[MAX] <-buffer of what client requested
**
*/
void receiveFile(int sockfd,char buff[MAX])
{
	printf("[Client] Receiveing file\n");
	char* file_recv = "clientFiles/received.txt";
	FILE *fr = fopen(file_recv, "a");
	int lSize;
	
	if(fr == NULL)
	{
		printf("File %s Cannot be opened.\n", file_recv);
	}
	else
	{
		int rSize = 0;
		printf("%s\n\n\n",buff);
		while((rSize = recv(sockfd, buff, MAXS, 0)) > 0)
		{
			lSize = fwrite(buff, sizeof(char), rSize, fr);
			if(lSize < rSize)
			{
				perror("File Write Failed.\n");
				exit(EXIT_FAILURE);
			}
			bzero(buff, MAXS);
			if (rSize == 0 || rSize != MAXS) 
			{
				break;
			}
		}
		if(rSize < 0)
		{
			if (errno == EAGAIN)
			{
				printf("File Timed Out.\n");
			}
			else
			{
				cout << "File Failed errno " << errno << endl;
			}
		}
		printf("FILE Recieved == \n\n");
		fclose(fr);
	}
	return;
}



void chat(int sockfd, char* message)
{
	char buff[MAXS]; 
	int connfd; 
	//char *MET[50];
	char *pch;
	char type[4];
	int i,n;	
	struct sockaddr_in servaddr;
	char userType[2];
	strcpy(type,"C1%");
	for (;;) 
	{ 
		connfd = connect(sockfd, (SA*)&servaddr, sizeof(servaddr)); 
			
		printf("[CLIENT]: "); 
		n = 0; 
		if (getchar() == '\n')
		{
			strcat(type,buff);
			strcat(type,"%");
			send(sockfd, type, RSIZE, 0);
			bzero(type,sizeof(type));
			bzero(buff,sizeof(buff));
		}
						
				
		read(sockfd, buff, sizeof(buff));
		cout << "[SERVER]: " << buff << endl;  
		bzero(buff,sizeof(buff));
		
	}
} 




/****************************
**Function 	serv
**Purpose 	Handle HTTP client requests
**Return 	N/A
**Input 	sockfd <-socket connection. .
**
*/

int serv (int sockfd, char* loginfo) 
{ 
	char buff[MAXS]; 
	int connfd; 
	//char *MET[50];
	//char *pch;
	//int i;	
	struct sockaddr_in servaddr;
	char userType[2];
		
		connfd = connect(sockfd, (SA*)&servaddr, sizeof(servaddr)); 
		
		bzero(buff,sizeof(buff));

		send(sockfd, loginfo, RSIZE,0);
		
		//bzero(loginfo, sizeof(loginfo)); // clear buffer after sending client response
		bzero(buff,sizeof(buff));
		
		if (read(sockfd, buff, sizeof(buff))!=NULL)
		{
		
			
			bzero(buff,sizeof(buff));
			read(sockfd,buff,sizeof(buff));
		
			if ((strncmp(buff, "1", 2)) == 0) 
			{ 
				//cout <<"BUFFER READ IN " << buff << endl;
				bzero(buff,sizeof(buff));
				return 1;
			}
			if ((strncmp(buff,"9",1)) == 0)
			{
				return 9;
			}
			else 
			{
				bzero(buff,sizeof(buff));
				return 0;
		
			}
		}
		//close(connfd);
	//}
} 


int connectToServer()
{
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	if (sockfd == 1)
	{
		cout << "\tSocket Failed\n";
		exit(EXIT_FAILURE);
	}
	else
		cout << "\tSocket Created Successfully\n";

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) !=0)
	{
		cout << "\tConnection Failure\n";
		exit(EXIT_FAILURE);
	}
	else
		cout << "\tConnected at " << PORT << endl;
	
	//serv(sockfd);
	
	//close(sockfd);
	return sockfd;
}

