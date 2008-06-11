#ifndef MESSAGE_H
#define MESSAGE_H

#define CRLF "\r\n"

#include <iostream> // FOR DEBUG ONLY
#include <string>
#include <vector>

#include "../../../tools/StringTokenizer.h"
#include "../../connection/IRCConnection.h"
#include "../../user/User.h"
#include "../../main/Channel.h"
#include "MessageFormat.h"

using namespace std;

class Message {
private:
    static vector<MessageFormat*> 	_registeredFormats;

    string				_raw;
    string				_prefix;
    string				_command;
    string				_friendly;
    vector<string> 			_params;
    unsigned int			_minparams;
    User*				_user;
    Channel*				_channel;
    
    const static MessageFormat*		_getFormatFor(Message* m);
    
    void				_init();
    void				_initUserMessage(StringTokenizer st);
    void				_initPrefixMessage(StringTokenizer st);
    void				_initNonPrefixMessage(StringTokenizer st);
    
public:

    Message(string raw);
    virtual ~Message();
        
    /*
     * Translates the raw string given during 
     * construction to a string that is fully 
     * compliant with RFC 1459.
     */
    string translate();
    
    /*
     * Returns the prefix of the message
     */
    const string prefix();
    
    /*
     * Returns the command of the message
     */
    const string command();
    
    /*
     * Returns the friendly form of the
     * command, if any.
     */
    const string friendly();
    
    /*
     * Returns the parameters that accompany 
     * this message.
     */
    const vector<string> params();
    
    /*
     * Returns the minimum amount of parameters
     * required for this message.
     */
    const unsigned int minParams();
    
    
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
     * Registers the format for a message.
     * This format contains the RFC command,
     * the skaar friendly command, and the
     * mimimum amount of parameters.
     */
    static void registerFormat(MessageFormat* mf);
    
    /*
     * Unregisters the format for a message. If 
     * a message is not registered, it cannot be sent.
     */
    static void unregisterFormat(MessageFormat* mf);

    /*
     * Checks if the supplied Message is registered.
     */
    static bool isRegistered(Message* m);
};

typedef Message* create_message_t(string raw);
typedef void destroy_message_t(Message*);

#endif
