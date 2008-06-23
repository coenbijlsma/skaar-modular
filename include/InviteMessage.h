#ifndef INVITEMESSAGE_H
#define INVITEMESSAGE_H

#define INVITEMESSAGE_COMMAND "INVITE"
#define INVITEMESSAGE_MINPARAMS 2
#define INVITEMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class InviteMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    InviteMessage(string raw);
    ~InviteMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef InviteMessage* create_invitemessage_t(string raw);
typedef void destroy_invitemessage_t(InviteMessage*);

#endif
