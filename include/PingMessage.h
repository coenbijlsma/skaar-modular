#ifndef PINGMESSAGE_H
#define PINGMESSAGE_H

#define PINGMESSAGE_COMMAND "PING"
#define PINGMESSAGE_MINPARAMS 1
#define PINGMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class PingMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    PingMessage(string raw);
    ~PingMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef PingMessage* create_pingmessage_t(string raw);
typedef void destroy_pingmessage_t(PingMessage*);

#endif
