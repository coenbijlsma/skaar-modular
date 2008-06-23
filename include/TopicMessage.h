#ifndef TOPICMESSAGE_H
#define TOPICMESSAGE_H

#define TOPICMESSAGE_COMMAND "TOPIC"
#define TOPICMESSAGE_MINPARAMS 2
#define TOPICMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class TopicMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    TopicMessage(string raw);
    ~TopicMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef TopicMessage* create_topicmessage_t(string raw);
typedef void destroy_topicmessage_t(TopicMessage*);

#endif
