#ifndef PASSMESSAGE_H
#define PASSMESSAGE_H

#define PASSMESSAGE_COMMAND "PASS"
#define PASSMESSAGE_MINPARAMS 1
#define PASSMESSAGE_MAXPARAMS 1

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class PassMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:

    PassMessage(string raw);
    ~PassMessage();
        
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);

    string 		command();
    unsigned int 	minParams();
};

typedef PassMessage* create_passmessage_t(string raw);
typedef void destroy_passmessage_t(PassMessage*);

#endif
