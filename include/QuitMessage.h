#ifndef QUITMESSAGE_H
#define QUITMESSAGE_H

#define QUITMESSAGE_COMMAND "QUIT"
#define QUITMESSAGE_MINPARAMS 0
#define QUITMESSAGE_MAXPARAMS 1

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class QuitMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:

    QuitMessage(string raw);
    ~QuitMessage();
        
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);

    string 		command();
    unsigned int 	minParams();
};

typedef QuitMessage* create_qmessage_t(string raw);
typedef void destroy_qmessage_t(QuitMessage*);

#endif
