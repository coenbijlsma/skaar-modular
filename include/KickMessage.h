#ifndef KICKMESSAGE_H
#define KICKMESSAGE_H

#define KICKMESSAGE_COMMAND "KICK"
#define KICKMESSAGE_MINPARAMS 2
#define KICKMESSAGE_MAXPARAMS 3

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class KickMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    KickMessage(string raw);
    ~KickMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef KickMessage* create_kickmessage_t(string raw);
typedef void destroy_kickmessage_t(KickMessage*);

#endif
