#ifndef QUITMESSAGE_H
#define QUITMESSAGE_H

#define CRLF "\r\n"

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "../../../tools/StringTokenizer.h"
#include "../../connection/IRCConnection.h"
#include "../../user/User.h"
#include "../../main/Channel.h"

using namespace std;

class QuitMessage {
private:
    string 		_command;
    vector<string> 	_params;
    User*		_user;
    Channel*		_channel;
    string		_raw;
    
    void		_init();
    
public:

    QuitMessage(string raw);
    virtual ~QuitMessage();
        
    /*
     * Translates the raw string given during 
     * construction to a string that is fully 
     * compliant with RFC 1459.
     */
    string translate();
    
    /*
     * Returns the command of the message
     */
    const string command();
    
    /*
     * Returns the parameters that accompany 
     * this message.
     */
    const vector<string> params();
    
    /*
     * Sets the User that sends this message
     */
    bool setUser(User* user);
    
    /*
     * Sets the channel this message 
     * is to be sent on.
     */
    bool setChannel(Channel* channel);
    
    /*
     * Actually transmits the message.
     */
    bool transmit(IRCConnection* conn);
    
    /*
     * Re-initializes the message with new
     * contents.
     */
    bool reInit(string raw);
};

typedef QuitMessage* create_qmessage_t(string);
typedef void destroy_qmessage_t(QuitMessage*);

#endif
