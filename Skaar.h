#ifndef SKAAR_H
#define SKAAR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "modules/core/ui/VirtualUI.h" 			// The UI
#include "modules/core/connection/IRCConnection.h" 	// The connection
#include "modules/core/user/User.h"			// The user
#include "modules/core/messages/Message.h"		// The messages

#define SKAAR_CONF "skaar.conf"
#define SKAAR_MODS_CONF "skaar_mods.conf"

using namespace std;

class Skaar {

private:
    IRCConnection* 		_connection;
    map<string, Message*>	_messages;
    User*			_user;
    vector<Channel*>		_channels;
    string			_host;
    int				_port;
    bool			_autoConnect;
    bool			_autoJoin;
    
public:

    Skaar(User* user		// The user that is connecting 
	, string host		// The IRC server to connect to
	, int port		// The port the server listens to
	, bool autoConnect	// Whether to automatically connect
	);
	
    virtual ~Skaar();
    
    /* 
     * Registers the UI to print output to,
     * and read input from. This defaults to
     * the stdin and stdout on the terminal.
     */
    bool registerUI(VirtualUI* ui);
    
    /*
     * Registers a message library that
     * is used for translating user-entered
     * strings to RFC 1459 compliant messages.
     */
    bool registerMessage(Message* m);
    
    /*
     * Registers the user to skaar.
     * If there is no user registerd,
     * skaar cannot connect.
     */
    bool registerUser(User* user);

    /*
     * Returns the channel the
     * User is currently active in.
     */
    Channel* getActiveChannel();
    
    /*
     * Calls the connection function in
     * the connection library.
     */
    bool connect();
    
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
