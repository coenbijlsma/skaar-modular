#ifndef MODEMESSAGE_H
#define MODEMESSAGE_H

#define MODEMESSAGE_COMMAND "MODE"
#define MODEMESSAGE_MINPARAMS 1
#define MODEMESSAGE_MAXPARAMS 5

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class ModeMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    ModeMessage(string raw);
    ~ModeMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef ModeMessage* create_modemessage_t(string raw);
typedef void destroy_modemessage_t(ModeMessage*);

#endif
