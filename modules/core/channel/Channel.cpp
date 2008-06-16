#include "Channel.h"

Channel::Channel(IRCConnection* conn, string name){
    if(name.empty()){
	throw "A channelname cannot be empty.\n";
    }
    if(conn == 0 || ! conn->connected()){
	throw "The connection for this channel cannot be empty.";
    }
    
    _connection = conn;
    _name 	= name;
}

Channel::~Channel(){}

const IRCConnection* Channel::getConnection(){
    return _connection;
}

const string Channel::getName(){
    return _name;
}

extern "C" Channel* create_channel(IRCConnection* conn, string name){
    return new Channel(conn, name);
}

extern "C" void destroy_channel(Channel* channel){
    delete channel;
}
