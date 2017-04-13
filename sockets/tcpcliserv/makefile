# Makefile for socket programs


all: tcpserv tcpcli

tcpserv: tcpserv.c
	gcc -o tcpserv tcpserv.c -lnsl 

tcpcli: tcpcli.c
	gcc -o tcpcli tcpcli.c -lnsl 

clean:
	rm tcpserv tcpcli