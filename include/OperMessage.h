#ifndef OPERMESSAGE_H
#define OPERMESSAGE_H

#define OPERMESSAGE_COMMAND "OPER"
#define OPERMESSAGE_MINPARAMS 1
#define OPERMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class OperMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    OperMessage(string raw);
    ~OperMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int	minParams();
};

typedef OperMessage* create_opermessage_t(string raw);
typedef void destroy_opermessage_t(OperMessage*);

#endif
