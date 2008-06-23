#ifndef TRACEMESSAGE_H
#define TRACEMESSAGE_H

#define TRACEMESSAGE_COMMAND "TRACE"
#define TRACEMESSAGE_MINPARAMS 0
#define TRACEMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class TraceMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    TraceMessage(string raw);
    ~TraceMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef TraceMessage* create_tracemessage_t(string raw);
typedef void destroy_tracemessage_t(TraceMessage*);

#endif
