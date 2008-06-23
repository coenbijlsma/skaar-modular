#ifndef WHOISMESSAGE_H
#define WHOISMESSAGE_H

#define WHOISMESSAGE_COMMAND "WHOIS"
#define WHOISMESSAGE_MINPARAMS 1
#define WHOISMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class WhoisMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    WhoisMessage(string raw);
    ~WhoisMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef WhoisMessage* create_whoismessage_t(string raw);
typedef void destroy_whoismessage_t(WhoisMessage*);

#endif
