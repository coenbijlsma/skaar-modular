#ifndef IRCMESSAGE_H
#define IRCMESSAGE_H

#include <string>
#include <vector>

#include "IRCConnection.h"
#include "User.h"
#include "Channel.h"

#ifndef IRCMESSAGE_MAXPARAMS
#define IRCMESSAGE_MAXPARAMS 15
#endif

#ifndef CRLF
#define CRLF "\n\r"
#endif

#ifndef SPACE
#define SPACE " "
#endif

#ifndef IRC_LINE_MAX
#define IRC_LINE_MAX 512
#endif

using namespace std;
    
class IRCMessage {
    
public:
    
    /*
     * Returns the command of the message
     */
    virtual const string command() =0;
    
    /*
     * Returns the minimum amount of 
     * parameters that this message needs.
     * This is needed to validate the message
     * before it gets out.
     */
    virtual const unsigned int minParams() =0;
    
    /*
     * Translates the raw message
     * to a RFC 1459 compliant string.
     */
    virtual string translate() =0;
    
    /*
     * Returns the prefix of the message.
     * The message only contains a prefix
     * when the message is sent from the 
     * server to the client.
     */
    virtual const string prefix() =0;
    
    /*
     * Returns the parameters that this
     * message contains.
     */
    virtual const vector<string> params() =0;
    
    /*
     * Sets the user who sends this message.
     */
    virtual void setUser(User* u) =0;
    
    /*
     * Actually transmits the message.
     * Returns false on failure, true on
     * success. A return value true does
     * not mean that the message has been delivered,
     * it only means that the message has been
     * sent successfully!
     */
    virtual bool transmit(IRCConnection* conn) =0;
    
};

#endif
