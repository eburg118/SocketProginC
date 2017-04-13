/***********************************************************************************
 *
 * Author: Eric Burgos
 * Creation Date: October 21, 2016
 * Modified Date: December 7, 2016
 * Filename: readme.txt
 * Purpose: Test plan
 * 
 *
 **********************************************************************************/
tcpcli.c is the client program that will be used to test the server program.
tcpserv.c is the server program that will be handling the connection/messages of the client.

To build(using makefile):
make tcpcli
make tcpserv

To run:
(first)./tcpserv [portnumber]
(then)./tcpcli [hostname][portnumber]

Test plan:
Client inputs nickname.
Server outputs: READY or RETRY
Client inputs "Hello".
Server outputs: "Hello" with the number of bytes in the string.
Client inputs: ./tcpcli hostname portnumber randomtext.
Client should give error and give usage clause. 

Development process:
I started out doing the client first and having it be ready to test the server.
This did not work out as I found it easier to work on both programs at once to
figure out exactly whats getting sent and received. Biggest problem was properly setting up the send and receive buffers.
Keeping track of what was in each buffer was hard. Was not sure if I only needed a send and receive buffer but I couldnt figure out how to properly flush them without having them overlap.




