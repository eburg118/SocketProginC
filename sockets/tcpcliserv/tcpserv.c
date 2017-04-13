/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 27, 2000
 * Modified Date: August 29, 2015
 * Filename: tcpserv.c
 * Purpose: Server example for TCP Sockets; reads one character at a time
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>

#define SIZE sizeof(struct sockaddr_in)


void catcher(int sig);
int newsockfd;


int main()
{
  int sockfd;
  char c;
  int pid;
  struct sockaddr_in server = {AF_INET, 7000, INADDR_ANY};
  static struct sigaction act;

  act.sa_handler = catcher;
  sigfillset(&(act.sa_mask));
  sigaction(SIGPIPE, &act, NULL);

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


  for (;;)
    {
      // accept connection
      // if returns an EINTR (interrupted system call) then can re-call
      while (((newsockfd = accept(sockfd, NULL, NULL)) == -1) && 
	     (errno == EINTR))
	;
      if (newsockfd == -1)
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
	  while (recv(newsockfd, &c, 1, 0) > 0)
	    {
	      c = toupper(c);
	      send(newsockfd, &c, 1, 0);
	    }   // end while

	  // when client is no longer sending information the
	  // socket can be closed and child process terminated
	  close(newsockfd);
	  exit(0);
	}   // end child process

      // parent doesn't need newsockfd
      close(newsockfd);
    }   // end for
}   // end main



void catcher(int sig)
{
  close(newsockfd);
  exit(0);
}   // end function catcher
