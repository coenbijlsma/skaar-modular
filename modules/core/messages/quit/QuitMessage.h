#ifndef QUITMESSAGE_H
#define QUITMESSAGE_H

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"
#include "StringTokenizer.h"

using namespace std;

class QuitMessage : public IRCMessage {
private:
    string				_raw;
    string				_prefix;
    string				_command;
    string				_friendly;
    vector<string> 			_params;
    unsigned int			_minparams;
    User*				_user;
    
    void				_init();
    void				_initFriendlyMessage(StringTokenizer st);
    void				_initMessage(StringTokenizer st);
    
public:

    QuitMessage(string raw);
    ~QuitMessage();
        
    string translate();
    
    const string command();
    
    const string friendly();
    
    const string prefix();
    
    const vector<string> params();
    
    const unsigned int minParams();
    
    bool setUser(User* user);
    
    bool transmit(IRCConnection* conn);
    
};

typedef QuitMessage* create_qmessage_t(string raw);
typedef void destroy_qmessage_t(QuitMessage*);

#endif
