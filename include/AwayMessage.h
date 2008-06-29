#ifndef AWAYMESSAGE_H
#define AWAYMESSAGE_H

#define AWAYMESSAGE_COMMAND "AWAY"
#define AWAYMESSAGE_MINPARAMS 0
#define AWAYMESSAGE_MAXPARAMS 1

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class AwayMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:

    AwayMessage(string raw);
    ~AwayMessage();
        
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);

    string 		command();
    unsigned int 	minParams();
};

typedef AwayMessage* create_awaymessage_t(string raw);
typedef void destroy_awaymessage_t(AwayMessage*);

#endif
