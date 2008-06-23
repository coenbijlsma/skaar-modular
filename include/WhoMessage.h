#ifndef WHOMESSAGE_H
#define WHOMESSAGE_H

#define WHOMESSAGE_COMMAND "WHO"
#define WHOMESSAGE_MINPARAMS 0
#define WHOMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class WhoMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    WhoMessage(string raw);
    ~WhoMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef WhoMessage* create_whomessage_t(string raw);
typedef void destroy_whomessage_t(WhoMessage*);

#endif
