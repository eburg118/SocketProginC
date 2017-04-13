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



#define SIZE sizeof(struct sockaddr_in)


void catcher(int sig);
int newsockfd;


int main()
{
  int sockfd;
  char c;
  int pid;
  int i, numChild = 0;
  struct timeval start, end;
 

  struct sockaddr_in server = {AF_INET, htons(15041), INADDR_ANY};
  static struct sigaction act;
  
  act.sa_handler = catcher;
  sigfillset(&(act.sa_mask));
  sigaction(SIGPIPE, &act, NULL);

  // set up the transport end point
  
  // Gets time of day since epoch(Jan 1, 1970)
  // Structured by tv_sec(seconds) and tc_usec(microseconds)
  if( gettimeofday(&start, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }
  
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket call failed");
      exit(-1);
    }   // end if 
  //Gets time of day after system call bind()
  if(gettimeofday(&end, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }
  
  // Calculations for finding difference between time
  printf("Start/End for socket() system call:\n");
  printf("Start- %ld.%06ld\n", start.tv_sec, start.tv_usec);
  printf("End- %ld.%06ld\n", end.tv_sec, end.tv_usec);
  // Output in microseconds
  printf("Total- %.ldμs\n\n", (end.tv_usec - start.tv_usec)*1);
  
  
  // Gets time of day since epoch(Jan 1, 1970)
  // Structured by tv_sec(seconds) and tc_usec(microseconds)
  if(gettimeofday(&start, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }
  // bind and address to the end point
  if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("bind call failed");
      exit(-1);
    }   // end if bind
  //Gets time of day after system call bind()
  if(gettimeofday(&end, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }
  // Calculations for finding difference between time  
  printf("Start/End for bind() system call:\n");
  printf("Start- %ld.%06ld\n", start.tv_sec, start.tv_usec);
  printf("End- %ld.%06ld\n", end.tv_sec, end.tv_usec);
  // Output in microseconds
  printf("Total- %.ldμs\n\n", (end.tv_usec - start.tv_usec)*1);


  // Gets time of day since epoch(Jan 1, 1970)
  if(gettimeofday(&start, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }
  // start listening for incoming connections
  if (listen(sockfd, 5) == -1)
    {
      perror("listen call failed");
      exit(-1);
    }   // end if

  //Gets time of day after system call listen()
  if(gettimeofday(&end, NULL) == -1)
    {
      perror("Error getting time");
      exit(-1);
    }

  // Calculations for finding difference between time
  printf("Start/End for listen() system call:\n");
  printf("Start- %ld.%06ld\n", start.tv_sec, start.tv_usec);
  printf("End- %ld.%06ld\n", end.tv_sec, end.tv_usec);
  // Output in microseconds
  printf("Total- %.ldμs\n\n", (end.tv_usec - start.tv_usec)*1);
  


  for (;;)
  {
      // accept connection
    if ((newsockfd = accept(sockfd, NULL, NULL)) == -1)
  	{
  	  perror("accept call failed");
  	  exit(-1);
  	}   // end if

      // spawn a child to deal with the connection
    if ((pid = fork()) == -1)
  	{
  	  perror("fork failed");
  	  exit(-1);
  	}   // end if

  if (pid == 0)
	{
	   str_echo(newsockfd);	/* process the request */

	  // when client is no longer sending information the
	  // socket can be closed and child process terminated
  	  close(newsockfd);
  	  exit(0);
  	}   // end child process

      // parent doesn't need newsockfd
    close(newsockfd);
    numChild++;
    }   // end for

  // wait for children
  for (i = 0; i < numChild; i--)
   wait();
}   // end main



void catcher(int sig)
{
  close(newsockfd);
  exit(0);
}   // end function catcher
