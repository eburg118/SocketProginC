#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

INCLUDE =

CLNTS = UDPtime
SERVS = UDPtimed daytimed

DEFS = -D_BSD_SOURCE
CFLAGS = -W -pedantic -ansi -g ${DEFS} ${INCLUDE}

HDR =
CSRC = UDPtime.c
CXSRC = connectUDP.c connectsock.c errexit.c

SSRC = UDPtimed.c daytimed.c
SXSRC = passiveUDP.c passivesock.c sv_funcs.c

CXOBJ = connectUDP.o connectsock.o errexit.o
SXOBJ = passiveTCP.o passiveUDP.o passivesock.o errexit.o

PROGS = ${CLNTS} ${SERVS}

all: ${PROGS}

${CLNTS}: ${CXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${CXOBJ}

${SERVS}: ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ}


clients: ${CLNTS}
servers: ${SERVS}

clean: 
	rm -f Makefile.bak a.out core errs ${PROGS} *.o


UDPtime: UDPtime.o
UDPtimed: UDPtimed.o
daytimed: daytimed.o
