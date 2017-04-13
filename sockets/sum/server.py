#!/usr/bin/python
#***************************************************************
#* 
#* Author: Dr. Lisa Frye
#* Date: August 28, 2015
#* Filename: echoServer.py
#* Purpose: Server example for TCP Sockets
#*                add two integers received from client
#*
#**************************************************************
import socket
import sys
import os

HOST = ''                 # Symbolic name meaning all available interfaces

# usage clause
if (len(sys.argv) != 2):
    print 'Usage: ', sys.argv[0], '<port_number>\n'
    sys.exit()

numChild = 0
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, int(sys.argv[1])))
s.listen(1)

# readlines function from https://synack.me/blog/using-python-tcp-sockets
#     retrieved 9/12/2015
def readlines(sock, recv_buffer=4096, delim='\n'):
    buffer = ''
    data = True
    while data:
        data = sock.recv(recv_buffer)
        buffer += data

        while buffer.find(delim) != -1:
            line, buffer = buffer.split('\n', 1)
            yield line
    return
    

# Child processing
def child(s, addr):
    sum = 0
    
    while 1:
        line = readlines(s)
        for num in line:
            print num
            num = num.rstrip()
            if (len(num) == 0):
                print 'sum = ', sum
                message = str(sum) + '\n'
                try:
                    s.sendall(message)
                    sum = 0
                except socket.error:
                    print 'Send failed'
                    break
            else:
                sum=sum+int(num)

   

    print 'child ended'
    # close child socket
    s.close()


# server code - listens for connections forever
while 1:
    clientSock, addr = s.accept()
    print 'Connected by', addr

    pid = os.fork()
    # Child process
    # catch CTRL-C interrups w ith KeyboardInterrupt and exit then
    if pid == 0:
        child(clientSock, addr)
    else:
        numChild+=1


# when server ends, wait for all children and close socket
for i in range(1, numChild):
    wait()

s.close()
