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
	gcc -o tcpserv tcpserv.c  $(LIBS)

tcpcli: tcpcli.c utils.o
	gcc -o tcpcli tcpcli.c  $(LIBS)


clean:
	/bin/rm -f tcpserv tcpcli 
	/bin/rm -f *.o