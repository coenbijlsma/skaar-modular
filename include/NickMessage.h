#ifndef NICKMESSAGE_H
#define NICKMESSAGE_H

#define NICKMESSAGE_COMMAND "NICK"
#define NICKMESSAGE_MINPARAMS 1
#define NICKMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class NickMessage : public IRCMessage {
private:
    string			_raw;
    vector<string> 		_params;
    User*			_user;
    
    void			_init();
    
public:
    
    NickMessage(string raw);
    ~NickMessage();
    
    string 			translate();
    const string 		prefix();
    const vector<string> 	params();
    void 			setUser(User* user);
    bool 			transmit(IRCConnection* conn);
    
    const string 		command();
    const unsigned int 		minParams();
};

typedef NickMessage* create_nickmessage_t(string raw);
typedef void destroy_nickmessage_t(NickMessage*);

#endif
