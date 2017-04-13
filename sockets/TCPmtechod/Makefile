#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

INCLUDE =

CLNTS = TCPecho TCPdaytime 
SERVS = TCPdaytimed
OTHER = TCPmtechod

DEFS = -D_BSD_SOURCE
CFLAGS = -W -pedantic -ansi -g ${DEFS} ${INCLUDE}

HDR =
CSRC = TCPecho.c TCPdaytime.c
CXSRC = connectTCP.c connectsock.c errexit.c

SSRC = TCPmtechod.c 
SXSRC = passiveTCP.c passivesock.c 

CXOBJ = connectTCP.o connectsock.o errexit.o
SXOBJ = passiveTCP.o passivesock.o errexit.o

PROGS = ${CLNTS} ${SERVS} ${OTHER}

all: ${PROGS}

${CLNTS}: ${CXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${CXOBJ}

${SERVS}: ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ}


TCPmtechod: TCPmtechod.o ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ} -lpthread

clients: ${CLNTS}
servers: ${SERVS}

clean: 
	rm -f Makefile.bak a.out core errs lint.errs ${PROGS} *.o


TCPdaytime: TCPdaytime.o
TCPdaytimed: TCPdaytimed.o
TCPecho: TCPecho.o
