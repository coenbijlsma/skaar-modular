#include "Skaar.h"

/* Registers the UI to print output to */
bool Skaar::_registerUI(VirtualUI* ui){
    _ui = ui;
}

/* Registers a RFC 1459 message for use */
bool _registerMessage(string name){
    /* Check if the message is already registered */
    for(int i = 0; i < _registeredMessages.size(); i++){
	if(name == _registeredMessages.at(i)){
	    return false;
	}
    }
    _registeredMessages.push_back(name);
    return true;
}

/* Registers the user to skaar */
bool _registerUser(User* user){
    if(_user == 0){
	_user = user;
	return true;
    }
    return false;
}

/* Constructor */
Skaar::Skaar(){
}

/* Destructor */
Skaar::~Skaar(){
    /* Write the config to the file. */
    _config->writeConfig();
    
    /* Clean up all the channels */
    _openChannels.clear();
        
    /* Disconnect from all servers and clean up */
    _connections.clear();
    
    delete _config;
    delete _user;
    delete _ui;
    
}

/* Initializes Skaar */
void Skaar::init(){
    _config = new SkaarConfig();
}

