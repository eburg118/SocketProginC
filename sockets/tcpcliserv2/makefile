# Makefile for socket programs

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS = -lnsl
endif
ifeq ($(OS), SunOS)
	LIBS = -lnsl -lsocket
endif


all: tcpserv tcpcli


tcpserv: tcpserv.c utils.o
	gcc -o tcpserv tcpserv.c utils.o $(LIBS)

tcpcli: tcpcli.c utils.o
	gcc -o tcpcli tcpcli.c utils.o $(LIBS)

utils.o: utils.c
	gcc -c utils.c

clean:
	/bin/rm -f tcpserv tcpcli 
	/bin/rm -f *.o