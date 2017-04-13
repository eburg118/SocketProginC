/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: August 29, 2015
 * Filename: Server.java
 * Purpose: Server example for TCP Sockets; add two integers received from client
 *
 **********************************************************************************/ 

import java.net.*;
import java.io.*;

public class Server {

    public static void main(String[] args) throws IOException {

        if (args.length != 1) {
            System.err.println("Usage: java Server <port number>");
            System.exit(1);
        }  // end if usage clause

        int portNumber = Integer.parseInt(args[0]);

	ServerSocket serverSocket = new ServerSocket(portNumber);

	try {
	    while (true) {
		// spawn a handler thread for client connection
		new Handler(serverSocket.accept()).start();
	    }  // end while
	} finally {
	    serverSocket.close();
	} // end finally
    }  // end function main


    /*********************************************************
     * A handler thread class to work with a single client.
     *********************************************************/
    private static class Handler extends Thread {
	private Socket socket;   // socket to use to connect to clients
	private PrintWriter out;
	private BufferedReader in;
	private String inputLine, outputLine;
	private String[] operands;
	private Integer sum;
	
	// Construct a handler thread
	public Handler(Socket socket) {
	    this.socket = socket;
	}  // end Handler


	// do the thread processing
	public void run() {
	    try {
		out = new PrintWriter(socket.getOutputStream(), true);
		in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	    
		inputLine = in.readLine();
		while (inputLine != null) {
		    operands = inputLine.split(" ");
		    sum = Integer.parseInt(operands[0]) + Integer.parseInt(operands[1]);
		    outputLine = String.valueOf(sum);
		    out.println(outputLine);
		    inputLine = in.readLine();
		}  // end while
		
	    } catch (IOException e) {
		System.out.println(e);
	    }  finally {
		try {
		    socket.close();
		}  catch (IOException e) {
		}  // end catch
	    }  // end finally
	    
	}  // end function run

    }  // end class Handler

}   // end class Server
