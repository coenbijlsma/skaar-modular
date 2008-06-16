#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#define USERMESSAGE_COMMAND "USER"
#define USERMESSAGE_MINPARAMS 4
#define USERMESSAGE_MAXPARAMS 4

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class UserMessage : public IRCMessage {
private:
    string			_raw;
    vector<string> 		_params;
    User*			_user;
    
    void			_init();
    
public:
    
    UserMessage(string raw);
    ~UserMessage();
    
    string 			translate();
    const string 		prefix();
    const vector<string> 	params();
    void 			setUser(User* user);
    bool 			transmit(IRCConnection* conn);
    
    const string 		command();
    const unsigned int 		minParams();
};

typedef UserMessage* create_usermessage_t(string raw);
typedef void destroy_usermessage_t(UserMessage*);

#endif
