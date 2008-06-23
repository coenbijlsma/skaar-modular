#ifndef ADMINMESSAGE_H
#define ADMINMESSAGE_H

#define ADMINMESSAGE_COMMAND "ADMIN"
#define ADMINMESSAGE_MINPARAMS 0
#define ADMINMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class AdminMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    AdminMessage(string raw);
    ~AdminMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef AdminMessage* create_adminmessage_t(string raw);
typedef void destroy_adminmessage_t(AdminMessage*);

#endif
