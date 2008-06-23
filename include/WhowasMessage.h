#ifndef WHOWASMESSAGE_H
#define WHOWASMESSAGE_H

#define WHOWASMESSAGE_COMMAND "WHOWAS"
#define WHOWASMESSAGE_MINPARAMS 1
#define WHOWASMESSAGE_MAXPARAMS 3

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class WhowasMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    WhowasMessage(string raw);
    ~WhowasMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef WhowasMessage* create_whowasmessage_t(string raw);
typedef void destroy_whowasmessage_t(WhowasMessage*);

#endif
