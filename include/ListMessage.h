#ifndef LISTMESSAGE_H
#define LISTMESSAGE_H

#define LISTMESSAGE_COMMAND "LIST"
#define LISTMESSAGE_MINPARAMS 0
#define LISTMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class ListMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    ListMessage(string raw);
    ~ListMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef ListMessage* create_listmessage_t(string raw);
typedef void destroy_listmessage_t(ListMessage*);

#endif
