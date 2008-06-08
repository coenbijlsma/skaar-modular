#include "IRCConnection.h"

IRCConnection::IRCConnection(char* host, int port){
    if(port == 0){
	_port = DEFAULT_PORT;
    }else{
	_port = port;
    }
    
    struct hostent *h = gethostbyname(host);
    
    if(h == 0){
	herror("gethostbyname");
	_host = host;
    }else{
	_host = inet_ntoa(*((struct in_addr*)h->h_addr));
    }
    
    _connected = true;
    
}

IRCConnection::~IRCConnection(){
    if(_connected){
	if(shutdown(_fd, SHUT_RDWR) == -1){
	    perror("shutdown 0");
	}else{
	    _connected = false;
	    if(close(_fd) == -1){
		perror("close");
	    }
	}
    }
}


bool IRCConnection::connected(){
    return _connected;
}

bool IRCConnection::createConnection(){
    if( (_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	perror("socket");
	return false;
    }
    
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family		= AF_INET;
    _addr.sin_port		= htons(_port);
    _addr.sin_addr.s_addr	= inet_addr(_host);
    
    if(connect(_fd, (struct sockaddr*)&_addr, sizeof(_addr)) == -1){
	close(_fd);
	perror("connect");
	return false;
    }
    
    printf("Connected to %s:%d\n", _host, _port);
    _connected = true;
    return true;
}

bool IRCConnection::disconnect(){
    if( ! _connected){
	printf("Only fools try to disconnect while not connected.\n");
	return false;
    }
    
    if(shutdown(_fd, SHUT_RDWR) == -1){
	perror("shutdown 1");
	return false;
    }
    
    _connected = false;
    if(close(_fd) == -1){
	perror("close");
	return false;
    }
    
    printf("You are now disconnected.\n");
    return true;
}

bool IRCConnection::sendMessage(char* msg){
    if( ! _connected){
	createConnection();
    }
    
    int bytes_sent;
    
    if(msg[strlen(msg)] != '\0'){
	msg[strlen(msg)] = '\0';
    }
    
    if( (bytes_sent = send(_fd, msg, strlen(msg), 0)) == -1 || bytes_sent != strlen(msg) ){
	perror("send");
	return false;
    }
    
    return true;
}

char* IRCConnection::readMessage(){
    if( ! _connected){
	fprintf(stderr, "Not connected!\n");
    }
    
    char* temp_msg = (char*)malloc(513);
    int msglen;
    memset(temp_msg, 0, 513);
    
    while(strlen(temp_msg) <= 512){
	char* chars = (char*)malloc(513);
	memset(chars, 0, 513);
	
	switch(recv(_fd, chars, 512, 0)){
	    case 0:
		return '\0';
	    case -1:
		perror("recv");
		return '\0';
	    default:
		strcat(temp_msg, chars);
	}
	
	msglen = strlen(temp_msg);
	break;
    }
    
    return temp_msg;
}

// CLASS FACTORIES

extern "C" IRCConnection* create(char* h, int p){
    return new IRCConnection(h, p);
}

extern "C" void destroy(IRCConnection* ic){
    delete ic;
}

