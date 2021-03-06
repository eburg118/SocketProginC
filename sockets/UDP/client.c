/***************************************************************************************
 * 
 * Author: Dr. Lisa Frye
 * Creation Date: November 10, 2000
 * Modified Date: August 29, 2015
 * Filename: client.c
 * Purpose: Client program for a UDP socket example
 *       Get character input, send one character at a time to server. Receiver
 *       upper-case version of character back from server and print to screen
 * Adapted from Haviland book
 **************************************************************************************/

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE sizeof(struct sockaddr_in)
#define MYPORT 50010
#define IPADDR "127.0.0.1"


main() 
{
  int sockfd;
  char c;

  // local port on the client
  struct sockaddr_in client = {AF_INET, INADDR_ANY, INADDR_ANY};

  // remote address of the server
  struct sockaddr_in server = {AF_INET, htons(MYPORT)};
  
  // convert and store the server's IP address
  server.sin_addr.s_addr = inet_addr(IPADDR);

  // set up the transport point
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
      perror("Socket call failed");
      exit(1);
    }   // end if socket

  // bind the local address to the end point
  if (bind(sockfd, (struct sockaddr *) &client, SIZE) == -1)
    {
      perror("bind call failed");
      exit(1);
    }   // end if bind


  // read a character from the keyboard
  while (read(0, &c, 1) != 0)
    {
      // send the character to the server
      if (sendto(sockfd, &c, 1, 0, (struct sockaddr *)&server, SIZE) == -1)
	{
	  perror("Client: sending");
	  continue;
	}  // end if sendto

      // receive the message back
      if (recv(sockfd, &c, 1, 0) == -1)
	{
	  perror("Client: receiving");
	  continue;
	}  // end recv

      write(1, &c, 1);
    }   // end while

}   // end main








