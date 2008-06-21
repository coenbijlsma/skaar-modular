#ifndef PARTMESSAGE_H
#define PARTMESSAGE_H

#define PARTMESSAGE_COMMAND "PART"
#define PARTMESSAGE_MINPARAMS 1
#define PARTMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class PartMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    PartMessage(string raw);
    ~PartMessage();
    
    string		translate();
    string 		prefix();
    vector<string> 	params();
    void		setUser(User* user);
    bool		transmit(IRCConnection* conn);
    
    string		command();
    unsigned int	minParams();
};

typedef PartMessage* create_partmessage_t(string raw);
typedef void destroy_partmessage_t(PartMessage*);

#endif
