Output for tcpserv.c:
-bash-4.1$ ./tcpserv
Start/End for socket() system call:
Start- 1477417001.448928
End- 1477417001.448939
Total- 11μs

Start/End for bind() system call:
Start- 1477417001.449006
End- 1477417001.449013
Total- 7μs

Start/End for listen() system call:
Start- 1477417001.449028
End- 1477417001.449033
Total- 5μs

AVG of 5 runs.
Total(socket call)- 12μs
Total(bind call)- 5μs
Total(listen call)- 5μs
------------------------------------------

Output for tcpcli.c:
-bash-3.00$ ./tcpcli
Start/End for socket() system call:
Start- 1477418413.448856s
End- 1477418413.448957s
Total- 101μs

Start/End for connect() system call:
Start- 1477418413.449304s
End- 1477418413.449674s
Total- 370μs

Server performed action!

AVG of 5 runs.
Total(socket call)- 100μs
Total(connect call)- 368μs
-------------------------------------------
ANALYSIS: The server side system calls had significantly lower
execution times(in terms of microseconds). Even when the same 
call was tested, the client side call took longer to execute. The 
client side has to deal with the handshaking and the
actual connection of the socket to the server socket which means
the system calls will take spend more time in execution.
