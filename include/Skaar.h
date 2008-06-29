#ifndef SKAAR_H
#define SKAAR_H

#define MESSAGECOUNT 29

#include <exception>
#include <map>
#include <string>
#include <string.h> // strcpy()
#include <sstream>
#include <vector>

#include "IRCConnection.h" 	// The connection
#include "GenericMessage.h"	// Incoming messages
#include "SkaarConfig.h"	// The configuration
#include "User.h"		// The user
#include "VirtualUI.h" 		// The UI
#include "Channel.h"
#include "SkaarLog.h"

#include "Mitm.h"		// Man In The Middle for messages

/* Exceptions */
#include "ConfigException.h"
#include "MessageException.h"
#include "UIException.h"


using namespace std;

class Skaar {

private:
    SkaarConfig* 		_config;
    SkaarLog*			_log;
    vector<IRCConnection*> 	_connections;
    vector<string>		_registeredMessages;
    map<string, string>		_messageAliases;
    map<string, Channel*>	_openChannels;
    User*			_user;
        
    void*			_dlUI; // UI library
    VirtualUI*			_ui;
    Channel*			_activeChannel;
    string			_messages[MESSAGECOUNT];

    /* 
     * Registers the UI to print output to,
     * and read input from. This defaults to
     * the stdin and stdout on the terminal.
     */
    bool _registerUI(VirtualUI* ui);
    
    /* 
     * Finds the UI to be loaded, and tries to load it.
     *
     * @throws UIException If loading the UI library fails.
     */
    void _initUI();
    
    /*
     * Destroys the provided VirtualUI*.
     */
    void _destroyUI(VirtualUI* ui);
    
    /*
     * Registers a command that represents
     * an RFC 1459 message. The command that is
     * registered must be present in RFC 1459.
     */
    bool _registerMessage(string name);
    
    /*
     * Registers the message aliases
     */
    void _registerMessageAliases();
    
    /*
     * Registers the user to skaar.
     * If there is no user registered,
     * skaar cannot connect.
     */
    bool _setUser(User* user);
    
    /*
     * Creates a connection to the 
     * provided server and registers 
     * the user.
     *
     * @throws MessageException if one of the 
     * messages fails.
     */
    bool _registerAt(string server, int port);
    
    /*
     * Handles the input from the IRCConnection*
     */
    void* _handleInput(void* ptr);
    
    /*
     * Handles the output to IRCConnection*
     *
     * @throws UIException if no UI is present.
     */
    void* _handleOutput(void* ptr);
    
    /*
     * Is called by pthread_create() and 
     * executes Skaar::_handleInput()
     */
    static void* _c_handleInput(void* ptr);
    
    /*
     * Is called by pthread_create() and
     * executes Skaar::_handleOutput()
     */
    static void _c_handleOutput(void* ptr);
    
    /*
     * Actually creates the threads for in- and output.
     */
    void _createThreads();
    
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
     *
     * @throws ConfigException if the
     * configuration isn't successfully read.
     */
    void startWork();
    
    /*
     * Returns the current user.
     */
    const User* getUser();
    
    /*
     * Checks if the provided alias is the alias
     * for the provided command.
     */
    bool isAliasFor(string alias, string command);
        
};

#endif
