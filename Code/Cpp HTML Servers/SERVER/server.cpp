#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "server.hpp"

#define MAX 2048
#define FILESZ 300
#define PORT 60001
#define htmlPSIZE 8000
#define SA struct sockaddr
/*********************
**Code Developed: Jarrod Resmondo
**		  Shane Bolding
**2/16/2020
**COP4635 Project 1
**
**TCP HTTP server
*/


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
	char send_buffer[MAX]; // no link between BUFSIZE and the file size
	int nb = fread(send_buffer, 1, sizeof(send_buffer), pFile);
	while(!feof(pFile)) 
	{
		//printf("PACKET:%s\n",send_buffer);
		write(nsockfd, send_buffer, nb);
		nb = fread(send_buffer, 1, sizeof(send_buffer), pFile);
		
	}
	printf("[SERVER]:\nFile Sent to CLIENT\n");
	printf("FILESIZE %ld\n",lSize);
	fclose(pFile);

}



/****************************
**Function 	settupHttpHeader
**Purpose 	Concatenate index.html to HTTP header for website information
**		Clear HTTP header
**Return 	N/A
**Input 	httpHeader  <-HTTP/1.1 200 OK
**
*/


void getHtml(char htmlPage[] ,char* filePath,int func)
{
	FILE *htmlData = fopen(filePath+1, "r");
	
	char line[FILESZ];
	char responseData[htmlPSIZE];

	strcpy(responseData,"");
	strcpy(line,"");

	if (func == 0)
	{
		while (fgets(line, FILESZ, htmlData) != 0) 
		{
			strcat(responseData, line);
		}
	
		strcat(htmlPage, responseData);
	}

	else if (func == 1)
	{
		strcpy(responseData,"");
		strcpy(line,"");
		strcpy(htmlPage,"");

	}
}

/****************************
**Function serv
**Purpose Handle HTTP client requests
**Return N/A
**Input sockfd <-socket connection. .
**
*/
void serv(int sockfd)
{
	int connfd;
	char *MET[50];
	char *pch;
	int i;	
	char buff[MAX]; 
	unsigned int len;
	struct sockaddr_in cli;
		
	char httpHeader[htmlPSIZE] = "HTTP/1.1 200 OK\r\n\n";

	len = sizeof(cli);
	
	for (;;) 
	{ 
		
		connfd = accept(sockfd, (SA*)&cli, &len);

		read(connfd, buff, sizeof(buff)); 
		printf("[CLIENT]:\n%s\n",buff); 
		printf("[SERVER]:\n");
	 	pch = strtok(buff, " ");
		i = 0;
		while (pch != NULL)
		{
			MET[i] = pch;
			pch = strtok (NULL," ");
			//printf("TOK[%d]:%s\n",i,MET[i]); //For printing tokens of the http header from client
			i++;
		}
		
		
		if(strncmp("GET",MET[0],3)==0)
		{
			if(strncmp("/404.html",MET[1],9) == 0)
			{
				getHtml(httpHeader,MET[1],0);
				send(connfd, httpHeader, sizeof(httpHeader),0);//send html page	
				close(connfd);
			}
			else if(strncmp("/page.html",MET[1],10) == 0)
			{
				getHtml(httpHeader, MET[1],0);
				send(connfd, httpHeader, sizeof(httpHeader),0);//send html page	
				
				
				close(connfd);
			}
			
			else if(strncmp("/images", MET[1], 7) == 0)
			{
				sendFile(connfd,MET[1]);	
				close(connfd);
			}
			else if(strncmp("/",MET[1],3) == 0)
			{
				getHtml(httpHeader,"/index.html",0);
				send(connfd, httpHeader, sizeof(httpHeader),0);//send html page	
				close(connfd);
			}		
				
			else 
			{
				getHtml(httpHeader, "/404.html", 0);
				send(connfd, httpHeader, sizeof(httpHeader),0);//send html page	
				close(connfd);
			}
		}
		if (strncmp("exit", buff, 4) == 0) 
		{ 
			printf("Server Exit...\n"); 
			break; 
		}
		getHtml(httpHeader,"",1);
		bzero(buff, MAX); 
		close(connfd);
	}



}


/****************************
**Function 	setupConn
**Purpose 	Setup connection.SOCKET Params BIND Listen and Accept a connection
**		Direct client requests
**Return 	0  <- exit to main
**Input 	N/A.
**
*/

int setupConn()
{
	int sockfd; 
	struct sockaddr_in servaddr; 
	
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) 
	{ 
		printf("Failed Socket errno = %d \n",errno); 
		exit(EXIT_FAILURE); 
	} 
	else
		printf("Connected: Port Number %d \n",PORT); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
	{ 
		printf("Binding Socket Failed\n"); 
		exit(EXIT_FAILURE); 
	} 
	else
		printf("Socket Bound\n"); 
	
	if ((listen(sockfd, 5)) != 0) 
	{ 
		printf("Server Listen Failed...\n"); 
		exit(EXIT_FAILURE); 
	} 
	else
		printf("Server Listening\n\n\n"); 
	

	serv(sockfd);
 
	return(0);

}	
