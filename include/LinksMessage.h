#ifndef LINKSMESSAGE_H
#define LINKSMESSAGE_H

#define LINKSMESSAGE_COMMAND "LINKS"
#define LINKSMESSAGE_MINPARAMS 0
#define LINKSMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class LinksMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    LinksMessage(string raw);
    ~LinksMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef LinksMessage* create_linksmessage_t(string raw);
typedef void destroy_linksmessage_t(LinksMessage*);

#endif
