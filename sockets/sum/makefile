
PROGS =	client server car sar
LIBS =  -lnsl -lresolv


all:	${PROGS}


client:	client.o utils.o
		gcc -o $@ client.o utils.o ${LIBS}

server:	server.o utils.o
		gcc -o $@ server.o utils.o ${LIBS}

car:	client.o utils.o 
		gcc -o $@ client.o utils.o -lnsl -lresolv

sar:	server.o utils.o 
		gcc -o $@ server.o utils.o -lnsl -lresolv


client.o: client.c
	gcc -c client.c

server.o: server.c
	gcc -c server.c

utils.o: utils.c
	gcc -c utils.c

clean:
	/bin/rm -f client server car sar
	/bin/rm -f *.o
	/bin/rm -f core
