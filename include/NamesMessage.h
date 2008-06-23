#ifndef NAMESMESSAGE_H
#define NAMESMESSAGE_H

#define NAMESMESSAGE_COMMAND "NAMES"
#define NAMESMESSAGE_MINPARAMS 0
#define NAMESMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class NamesMessage : public IRCMessage {
private:
    string		_raw;
    vector<string>	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    NamesMessage(string raw);
    ~NamesMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int	minParams();
};

typedef NamesMessage* create_namesmessage_t(string raw);
typedef void destroy_namesmessage_t(NamesMessage*);

#endif
