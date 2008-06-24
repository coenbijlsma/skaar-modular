#ifndef CHANNEL_H
#define CHANNEL_H

#define CHAN_NETWORK '#' // RFC 1459
#define CHAN_LOCAL '&' // RFC 1459

#include <string>
#include "IRCConnection.h"

using namespace std;

class Channel {
private:
    IRCConnection*	_connection;
    string 		_name;
    char		_type;
    string		_topic;
        
public:
    Channel(IRCConnection* conn, string name);
    ~Channel();
    
    const IRCConnection* getConnection();
    string getName();
    char getType();
    string getTopic();
    void setTopic(string topic);
    
};

typedef Channel* create_channel_t(IRCConnection*, string);
typedef void destroy_channel_t(Channel*);

#endif
