#ifndef VERSIONMESSAGE_H
#define VERSIONMESSAGE_H

#define VERSIONMESSAGE_COMMAND "VERSION"
#define VERSIONMESSAGE_MINPARAMS 0
#define VERSIONMESSAGE_MAXPARAMS 1

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class VersionMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    VersionMessage(string raw);
    ~VersionMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef VersionMessage* create_versionmessage_t(string raw);
typedef void destroy_versionmessage_t(VersionMessage*);

#endif
