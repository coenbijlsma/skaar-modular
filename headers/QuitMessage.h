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

////////////////////////////////////////////////////////////////////////////////
//				OBJECT VARIABLES			      //
////////////////////////////////////////////////////////////////////////////////

    string				_raw;
    vector<string>			_friendlies;
    vector<string> 			_params;
    User*				_user;
    
    void				_init();

////////////////////////////////////////////////////////////////////////////////
//				CLASS VARIABLES				      //
////////////////////////////////////////////////////////////////////////////////

    static const string			_command 	= "QUIT";    
    static const unsigned int		_minparams 	= 0;
    
public:

    QuitMessage(string raw);
    ~QuitMessage();
        
    string translate();
    
    const string friendly();
    
    const string prefix();
    
    const vector<string> params();
    
    bool setUser(User* user);
    
    bool transmit(IRCConnection* conn);


    static const string 	command();
    static const unsigned int 	minParams();
};

typedef QuitMessage* create_qmessage_t(string raw);
typedef void destroy_qmessage_t(QuitMessage*);

#endif
