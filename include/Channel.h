#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include "IRCConnection.h"

using namespace std;

class Channel {
private:
    IRCConnection*	_connection;
    string 		_name;
    string		_topic;
        
public:
    Channel(IRCConnection* conn, string name);
    ~Channel();
    
    const IRCConnection* getConnection();
    string getName();
    string getTopic();
    void setTopic(string topic);
    
};

typedef Channel* create_channel_t(IRCConnection*, string);
typedef void destroy_channel_t(Channel*);

#endif
