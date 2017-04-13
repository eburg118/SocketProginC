/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 27, 2000
 * Modified Date: August 29, 2015
 * Filename: tcpcli.c
 * Purpose: Client example for TCP Sockets; sends one charater at a time
 * Adapted from Haviland book
 ***********************************************************************************/ 
/***************************************************************************
 * Author: ERIC BURGOS
 * Creation Date: November 27, 2000
 * Modified Date: November, 6 2016
 * Filename: tcpcli.c
 * Purpose: Client example for TCP Sockets; receives a quote 
 * and displays it from specified QOTD server.
 * **************************************************************************/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
void catcher(int sig);
int hostnameToIP(char * , char *);

#define SIZE sizeof(struct sockaddr_in)
#define MAXSIZE 1024

int main(int argc, char *argv[] )
{
  //  char rdybuff[5];
  int sockfd;
  char *rc[100];
  struct sockaddr_in server;
  char *hostname = "localhost";
  int portNum;     
  int flag1 = 0;
  char ip[100];
  ssize_t numofBytes;
  //ssize_t rdybuff;
  char buffer[100];
  //char buff[1000];
  char nick[10];
  int num, num1;
  char randNick[10] = "Rick";
  char bufferR[100];
  int rdyy;
  //static struct sigaction act;
  //act.sa_handler = catcher;
  //sigfillset(&(act.sa_mask));
  //sigaction(SIGINT, &act, NULL);

  // Will check to see if there is at least one command-line argument specified 
  //printf("Specify a hostname and optionally a port number to connect to \n")

  //Usage Clause
  switch (argc)
    {
    case 1:
      printf("Please specify a hostname\n");
      fprintf(stderr, "Usage: %s [hostname]\n", argv[0]);
      printf("Or, Usage: %s [hostname] [port number]\n", argv[0]);
      exit(EXIT_FAILURE);
      break;
    case 3:
      portNum = atoi(argv[2]);
      flag1 = 1;
    case 2: 
      hostname = argv[1];
      break;
    case 4:
      printf("Too many arguments\n");
      exit(-1);
      break;
    default:
      printf("Please specify a hostname\n");
      fprintf(stderr, "Usage: %s [hostname]\n", argv[0]);
      printf("Or, Usage: %s [hostname] [port number]\n", argv[0]);
      exit(EXIT_FAILURE);
          
    }

  // Call to function that will change hostname to IP address
  hostnameToIP(hostname, ip);
  
  // Will print hostname and IP
  printf("Hostname: %s\n", hostname );
  printf("IP address of %s: %s\n", hostname, ip);
  //printf("Port number: $\n", portNum);  
  // convert and store the server's IP address
  server.sin_family = AF_INET;
  // Switch to handle portnumber assignment
  switch (flag1)
    {
    case 1:
      server.sin_port = htons(portNum);
      break;
    default:
      server.sin_port = htons(15041);
    }
  server.sin_addr.s_addr = inet_addr(ip);
  
  // set up the transport end point for communication
  // IPv4 Internet protocols
  // SOCK_STREAM. socket type. Reliable 2 way connection-based byte streams.
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket call failed");
      exit(-1);
    }   // end if

  // Initiate connection
  // connect the socket to the server's address
  if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("connect call failed");
      exit(-1);
    }   // end if
  
  // Receiving HELLo from server  
  char helloMsg[6];
  num = recv(sockfd, helloMsg, sizeof(helloMsg),0);
  if ( num <= 0 )
    {
      printf("Either Connection Closed or Error\n");
      
    }
  helloMsg[num] = '\0';
  printf("Message Received -  %s\n",helloMsg);
  //memset(nick, '/0', 20);
  //  while(1)
  //{
  //Getting keyboard input from user
 
  printf("Enter a nickname: ");
  fgets(nick, MAXSIZE-1, stdin);
  // sending nickname to server
  if ((send(sockfd, nick, strlen(nick),0))== -1) 
    {
      fprintf(stderr, "Failure Sending Message\n");
      close(sockfd);
      //exit(1);
      //break;
    }
  printf("READY\n");
    
 
  while(1) {
    // Getting keyboard input, putting in a buffer and sending to socket
    //      memset(buffer,0,256);      
    printf("Enter Data for Server:\n");
    fgets(buffer,MAXSIZE-1,stdin);
    if ((send(sockfd,buffer, strlen(buffer),0))== -1) {
      fprintf(stderr, "Failure Sending Message\n");
      close(sockfd);
      exit(1);
    }
      else {
	//    printf("Client:Message being sent: %s\n",buffer);
	memset(bufferR,0,sizeof(buffer));	
	num1 = recv(sockfd, bufferR, sizeof(bufferR),0);
	if ( num1 <= 0 )
	  {
	    printf("Either Connection Closed or Error\n");
	    //Break from the While
	    break;
	  }
	
	//bufferR[num1] = '\0';

	printf("Client:Message Received From Server -  %s, # of bytes %d:\n",bufferR, num1-1);
	//memset(bufferR,'\0',100);
      }
    }
    close(sockfd);
}  // end main


int hostnameToIP(char * hostname , char* ip)
{
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_in *h;
  int c;
  // Fill memory pointed to by hints  
  memset(&hints, 0, sizeof hints);
  // Specify address family(internet) and socket type(TCP)
  hints.ai_family = AF_INET; 
  hints.ai_socktype = SOCK_STREAM;
  
  // Gets hostname ready for network translation
  if ( (c = getaddrinfo( hostname , "http" , &hints , &servinfo)) != 0) 
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(c));
      exit(-1);
    }
  
  // loop through all the results and connect to first available result
  for(p = servinfo; p != NULL; p = p->ai_next) 
    {
      h = (struct sockaddr_in *) p->ai_addr;
      strcpy(ip , inet_ntoa( h->sin_addr ) );
    }
  
  // Frees memory that was allocated
  freeaddrinfo(servinfo); 
  return 0;
}

//void catcher(int sig)
//{
// printf("Server received interrupt signal, closing...");
// close(newsockfd);
// exit(0);
//}   // end function catcher


