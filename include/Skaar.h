#ifndef SKAAR_H
#define SKAAR_H

#include <map>
#include <string>
#include <vector>

#include "IRCConnection.h" 	// The connection
//#include "IRCMessage.h"		// The messages
#include "SkaarConfig.h"	// The configuration
#include "User.h"		// The user
#include "VirtualUI.h" 		// The UI
#include "Channel.h"

using namespace std;

class Skaar {

private:
    SkaarConfig* 		_config;
    vector<IRCConnection*> 	_connections;
    vector<string>		_registeredMessages;
    map<string, string>		_messageAliases;
    map<string, Channel*>	_openChannels;
    User*			_user;
    
    void*			_dlUI;
    VirtualUI*			_ui;
    
    IRCConnection*		_activeConnection;
    Channel*			_activeChannel;
        
    /* 
     * Registers the UI to print output to,
     * and read input from. This defaults to
     * the stdin and stdout on the terminal.
     */
    bool _registerUI(VirtualUI* ui);
    
    /*
     * Registers a command that represents
     * an RFC 1459 message. The command that is
     * registered must be present in RFC 1459.
     */
    bool _registerMessage(string name);
    
    /*
     * Registers the user to skaar.
     * If there is no user registered,
     * skaar cannot connect.
     */
    bool _setUser(User* user);
    
public:

    Skaar();
    virtual ~Skaar();
    
    /*
     * Initiates Skaar.
     * Reads the config file and starts
     * accordingly.
     */
    void init();
    
    /*
     * Registers an alias for a message. The message
     * must be a message that exists in RFC 1459.
     * For example, RFC 1459 contains the message
     * JOIN, and you could register an 
     * alias named join, and an alias named j.
     * That way, when you want to join a channel 
     * you can type /join or /j instead of /JOIN
     * to join a channel. You can find the most common
     * message aliases in the config file skaar.conf,
     * but you can also register temporary aliases that 
     * last as long as skaar is running by using the command
     * /alias. See the header file of this command for more 
     * information about this.
     */
    bool registerMessageAlias(string message, string alias);

    /*
     * Returns the channel the
     * User is currently active in.
     */
    Channel* getActiveChannel();
    
    /*
     * After skaar has been initiated,
     * the real work can begin. It does 
     * so here.
     */
    void startWork();
    
    /*
     * Returns the current user.
     */
    const User* getUser();
        
};

#endif
