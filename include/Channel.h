#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include "IRCConnection.h"

using namespace std;

class Channel {
private:
    IRCConnection*	_connection;
    string 		_name;
        
public:
    Channel(IRCConnection* conn, string name);
    ~Channel();
    
    const IRCConnection* getConnection();
    const string getName();
};

typedef Channel* create_channel_t(IRCConnection*, string);
typedef void destroy_channel_t(Channel*);

#endif
