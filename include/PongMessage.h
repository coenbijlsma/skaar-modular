#ifndef PONGMESSAGE_H
#define PONGMESSAGE_H

#define PONGMESSAGE_COMMAND "PONG"
#define PONGMESSAGE_MINPARAMS 1
#define PONGMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class PongMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    PongMessage(string raw);
    ~PongMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef PongMessage* create_pongmessage_t(string raw);
typedef void destroy_pongmessage_t(PongMessage*);

#endif
