/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 27, 2000
 * Modified Date: August 29, 2015
 * Filename: tcpcli.c
 * Purpose: Client example for TCP Sockets; sends one charater at a time
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE sizeof(struct sockaddr_in)
#define IPADDR   "127.0.0.1"   

int main()
{
  int sockfd;
  char c, rc;
  struct sockaddr_in server = {AF_INET, 7000};


  // convert and store the server's IP address
  server.sin_addr.s_addr = inet_addr(IPADDR);
  
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
  // 
  if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("connect call failed");
      exit(-1);
    }   // end if

  // send and receive information with the server
  for (rc = '\n';;)
    {
      if (rc == '\n')
	printf("Input a lower case character: ");
      c = getchar();
      send(sockfd, &c, 1, 0);

      if (recv(sockfd, &rc, 1, 0) > 0)
	printf("%c", rc);
      else
	{
	  printf("server has died\n");
	  close(sockfd);
	  exit(-1);
	}   // end else
    }  // end for
}  // end main
