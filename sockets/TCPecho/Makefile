#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

INCLUDE =

CLNTS = TCPecho
SERVS = TCPechod 

DEFS = -D_BSD_SOURCE
CFLAGS = -W -pedantic -ansi -g ${DEFS} ${INCLUDE}

CSRC = TCPecho.c 
CXSRC = connectTCP.c connectsock.c errexit.c

SSRC = TCPechod.c 
SXSRC = passiveTCP.c passivesock.c

CXOBJ = connectTCP.o connectsock.o errexit.o
SXOBJ = passiveTCP.o passivesock.o errexit.o

PROGS = ${CLNTS} ${SERVS} 

all: ${PROGS}

${CLNTS}: ${CXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${CXOBJ}

${SERVS}: ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ}


clean: 
	rm -f Makefile.bak a.out core ${PROGS} *.o


TCPecho: TCPecho.o
TCPechod: TCPechod.o
