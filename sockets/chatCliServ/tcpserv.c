/***********************************************************************************
 *
 * Author: Eric Burgos
 * Creation Date: October 21, 2016
 * Modified Date: October 24, 2016
 * Filename: tcpserv.c
 * Purpose: Server example for TCP Sockets; receives one string at a time
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>


#define SIZE sizeof(struct sockaddr_in)


void catcher(int sig);
int newsockfd;
#define MAXSIZE 1024

int main(int argc, char *argv[])
{
  int READY;
  char recvv[9];
  int sockfd;
  char c;
  int pid, inSize;
  char cliMsg[100];
  char buffer[100];
  char randomName[5] = "Rick";
  int num;
  int i, numChild = 0;
  int portNum = 15041;
  char nickMsg[10];
  struct sockaddr_in server = {AF_INET, htons(15041), INADDR_ANY};
  
  
  if (argc > 2)  
    {
      fprintf(stderr, "Usage: %s [port number]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  //signal handler for Ctrl-c
  static struct sigaction act;
  
  act.sa_handler = catcher;
  sigfillset(&(act.sa_mask));
  sigaction(SIGINT, &act, NULL);
  
  // set up the transport end point
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket call failed");
      exit(-1);
    }   // end if 
  
  // bind and address to the end point
  if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("bind call failed");
      exit(-1);
    }   // end if bind

  // start listening for incoming connections
  if (listen(sockfd, 5) == -1)
    {
      perror("listen call failed");
      exit(-1);
    }   // end if
  
  // accept connection and send HELLO to new client
  while(1)
    { 
      if ((newsockfd = accept(sockfd, NULL, NULL)) == -1)
	{
	  perror("accept call failed");
	  exit(-1);
	}   // end if
      if (accept)
	{
	  char msgg[6] = "HELLO";
	  printf("Connection successful\n");
	  write(newsockfd, msgg, sizeof(msgg));
	} 
    

  //Break;    
  //      if ((num = recv(newsockfd, nickMsg, 6, 0)) == -1 )
      //{
      //	  perror("Error recv\n");
      //	  exit(1);
      //	}
      //else if (num == 0)
      //	{
      //	  printf("No input from client\n");
      //	  break;
      //	}

      num = recv(newsockfd, nickMsg,sizeof(nickMsg), 0);
      if(num <= 0)
	{
	  printf("Connection closed or error\n");
	  break;
	}   
      
	  //if(strlen(nickMsg))
	  //buffer[nickMsg] = '\0';
	  //printf("Client nickname = $s\n", nickMsg);
	  //memset(nickMsg, 0, 6);
	  //	nickMsg[num] = "\0";
      
      fprintf(stdout,"Client Nickname: %s", nickMsg);
      // nested while loop for receiving and sending 
      while(1){ 
	
	if ((inSize = recv(newsockfd, cliMsg, 1000, 0)) == -1 )
	  {
	    perror("Error recv\n");
	    exit(1);
	  }
	else if (inSize == 0)
	  {
	    printf("No input from client or client disconnected\n");
	    break;
	  }
	//	memset(recvv,)
	
	cliMsg[inSize] = '\0';
	fprintf(stdout, "Msg Received: %s \n", cliMsg);
	strcpy(recvv, "RECEIVED");
	if ((send(newsockfd, recvv, strlen(cliMsg),0))== -1)
          {
            fprintf(stderr, "Failure Sending Message\n");
            close(newsockfd);
            break;
          }
		
	
      }
    }
  
  //	  str_echo(newsockfd);	/* process the request */	  
  // when client is no longer sending information the
  // socket can be closed and child process terminated
  close(newsockfd);
  
  //exit(0);
  // end child process
  
      // parent doesn't need newsockfd
  close(newsockfd);
  
  
  // end main
}
void catcher(int signal)
{
  printf("Closing in 5 seconds..\n");
  send(newsockfd, "Server closing in 5 seconds..\n", 30, 0);
  sleep(5);
  close(newsockfd);
  exit(0);
}   // end function catcher
