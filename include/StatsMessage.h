#ifndef STATSMESSAGE_H
#define STATSMESSAGE_H

#define STATSMESSAGE_COMMAND "STATS"
#define STATSMESSAGE_MINPARAMS 0
#define STATSMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class StatsMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    StatsMessage(string raw);
    ~StatsMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef StatsMessage* create_statsmessage_t(string raw);
typedef void destroy_statsmessage_t(StatsMessage*);

#endif
