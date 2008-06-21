#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H

#define JOINMESSAGE_COMMAND "JOIN"
#define JOINMESSAGE_MINPARAMS 1
#define JOINMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class JoinMessage : public IRCMessage {
private:
    string		_raw;
    vector<string>	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    JoinMessage(string raw);
    ~JoinMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int	minParams();
};

typedef JoinMessage* create_joinmessage_t(string raw);
typedef void destroy_joinmessage_t(JoinMessage*);

#endif
