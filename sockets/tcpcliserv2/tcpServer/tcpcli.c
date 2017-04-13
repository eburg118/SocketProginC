
/***********************************************************************************
 *
 * Author: Eric Burgos
 * Creation Date: October 21, 2016
 * Modified Date: October 24, 2016
 * Filename: tcpcli.c
 * Purpose: Client example for TCP Sockets; sends one string at a time 
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>


#define SIZE sizeof(struct sockaddr_in)
//#define IPADDR   "127.0.0.1"  // localhost
#define IPADDR   "156.12.127.18"  // csit
//#define IPADDR   "156.12.127.9"   // harry
//#define IPADDR   "156.12.127.10"  // hermione

int main()
{
  struct timeval start, end;
  int sockfd;
  int connectJawn;  
  time_t startT, endT;
  char c, rc;
  struct sockaddr_in server;
  double elapsedTime;

  server.sin_family = AF_INET;
  server.sin_port = htons(15041);
  // convert and store the server's IP address
  server.sin_addr.s_addr = inet_addr(IPADDR);
  
  
  // Gets time of day since epoch(Jan 1, 1970)
  // Structured by tv_sec(seconds) and tc_usec(microseconds)
  gettimeofday(&start, NULL);
  // set up the transport end point
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  //Gets time of day after system call bind()
  gettimeofday(&end, NULL);

  // Calculations for finding difference between time
  printf("Start/End for socket() system call:\n");
  printf("Start- %ld.%06lds\n", start.tv_sec, start.tv_usec);
  printf("End- %ld.%06lds\n", end.tv_sec, end.tv_usec);
  // Output in microseconds
  printf("Total- %.ldμs\n\n", (end.tv_usec - start.tv_usec)*1);

  if (sockfd  == -1)
    {
      perror("socket call failed");
      exit(-1);

    }   // end if

  // Gets time of day since epoch(Jan 1, 1970)
  // Structured by tv_sec(seconds) and tc_usec(microseconds)
  gettimeofday(&start, NULL);

  // connect the socket to the server's address
  connectJawn = connect(sockfd, (struct sockaddr *)&server, SIZE);

  //Gets time of day after system call bind()
  gettimeofday(&end, NULL);

  // Calculations for finding difference between time  
  printf("Start/End for connect() system call:\n");
  printf("Start- %ld.%06lds\n", start.tv_sec, start.tv_usec);
  printf("End- %ld.%06lds\n", end.tv_sec, end.tv_usec);
  // Output in microseconds
  printf("Total- %.ldμs\n\n", (end.tv_usec - start.tv_usec)*1);
 
  if (connectJawn == -1)
    {
      perror("connect call failed");
      exit(-1);
    }   // end if

  
  
    str_cli("Hello World!\n", sockfd);		/* do it all */

}  // end main
