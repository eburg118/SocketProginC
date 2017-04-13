# Makefile for socket programs


all: server client


server: server.c
	gcc -o server server.c -lnsl

client: client.c
	gcc -o client client.c -lnsl

clean:
	/bin/rm -rf client server
