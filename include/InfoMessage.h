#ifndef INFOMESSAGE_H
#define INFOMESSAGE_H

#define INFOMESSAGE_COMMAND "INFO"
#define INFOMESSAGE_MINPARAMS 0
#define INFOMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class InfoMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    InfoMessage(string raw);
    ~InfoMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef InfoMessage* create_infomessage_t(string raw);
typedef void destroy_infomessage_t(InfoMessage*);

#endif
