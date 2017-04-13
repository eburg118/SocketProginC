/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 10, 2000
 * Modified Date: August 29, 2015
 * Filename: server.c
 * Purpose: Server example for TCP Sockets; add two integers received from client
 * Adapted from Stevens, UNIX Network Programming, Vol 1
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#define LISTENQ   1024


struct args
{
  long arg1;
  long arg2;
};

struct result
{
  long sum;
};


void find_sum(int sockfd);
void sig_chld(int signo);


int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	int			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

	if (argc != 2)
	  {
	    printf("\nusage: %s <port_number>\n\n", argv[0]);
	    exit(1);
	  }

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		
		// catch the signal when a child process dies
		// Why does this have to be in the for loop?
		// only catches first child when outside for loop
		signal(SIGCHLD, sig_chld);

		if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
			if (errno == EINTR)
				continue;		/* back to for() */
			else
			  {
				perror("accept error");
				exit(-1);
			  }   // end else
		}

		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);	/* close listening socket */
			find_sum(connfd);	/* process the request */
			exit(0);
		}
		close(connfd);			/* parent closes connected socket */
	}
}



void find_sum(int sockfd)
{
	ssize_t			n;
	struct args		args;
	struct result	result;

	for ( ; ; ) {
		if ( (n = readn(sockfd, &args, sizeof(args))) == 0)
			return;		/* connection closed by other end */

		result.sum = args.arg1 + args.arg2;
		writen(sockfd, &result, sizeof(result));
	}
}



void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
