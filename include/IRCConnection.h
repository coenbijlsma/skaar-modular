/*
 * File: IRCConnection.h
*/

#ifndef IRCCONNECTION_H
#define IRCCONNECTION_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <poll.h>

#define DEFAULT_PORT 6667

using namespace std;

/*
 * This is the header file for the library libircconnection.so.1.0 .
 * libircconnection is part of the core of libraries that keep skaar
 * running; be careful if you change anything.
 */
class IRCConnection{
    int 		_fd;
    bool 		_connected;
    struct sockaddr_in 	_addr;
    char* 		_host;
    int 		_port;
    struct pollfd	_pfd[1];
    int			_pollTimeoutMSecs; // Let poll() return immediately

public:
    IRCConnection(char* host, int port);
    virtual ~IRCConnection();
    
    /*
     * Returns whether there is a connection
     * to an IRC server.
     */
    bool 	connected();
    
    /*
     * Creates a connection to the server
     * host:port.
     */
    bool 	createConnection();
    
    /*
     * Disconnects from the server.
     */
    bool 	disconnect();
    
    /*
     * Sends a message to the server.
     */
    bool 	sendMessage(string msg);
    
    /*
     * Retrieves a message from the server
     */
    char* 	readMessage();
    
    /*
     * Polls the connection for events.
     * See also poll(3)
     */
    int		pollConnection();
};

/*
 * Because dlsym() is not able to load class-
 * definitions, but only functions. These functions
 * take care of constructing an destructing objects.
 */
typedef IRCConnection* create_connection(char* h, int p);
typedef void destroy_connection(IRCConnection*);

#endif
