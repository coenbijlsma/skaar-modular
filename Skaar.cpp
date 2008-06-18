#include "Skaar.h"

#include <dlfcn.h> // libraries

/* Registers the UI to print output to */
bool Skaar::_registerUI(VirtualUI* ui){
    _ui = ui;
}

/* Registers a RFC 1459 message for use */
bool Skaar::_registerMessage(string name){
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
bool Skaar::_setUser(User* user){
    if(_user == 0){
	_user = user;
	return true;
    }
    return false;
}

/* Constructor */
Skaar::Skaar(){}

/* Destructor */
Skaar::~Skaar(){
    /* Clean up all the channels */
    _openChannels.clear();
        
    /* Disconnect from all servers and clean up */
    _connections.clear();
    
    delete _config;
    delete _user;
    
    /* Load destroy symbol */
    destroy_ui_t* destroy_ui = (destroy_ui_t*) dlsym(_dlUI, "destroy_ui");
    
    /* Clean up the UI */
    destroy_ui(_ui);
    dlclose(_dlUI);
}

/* Initializes Skaar */
void Skaar::init(){
    _config = new SkaarConfig();
    
    string UIlib = _config->getValue(string("core"), string("ui"));
    string _error;
    
    _dlUI = dlopen(UIlib.c_str(), RTLD_LAZY);
    
    if( ! _dlUI){
	cerr << "Cannot load library " << UIlib << ": " << dlerror() << " Trying default UI." << endl;
	
	_dlUI = dlopen(_config->getValue(string("core"), string("defaultui")).c_str(), RTLD_LAZY );
	
	if( ! _dlUI){
	    throw "Cannot load default ui, exiting.";
	}
    }
    
    /* Reset dlerror() */
    dlerror();
    
    /* Load create symbol */
    create_ui_t* create_ui = (create_ui_t*) dlsym(_dlUI, "create_ui");
    const char* dlsym_error = dlerror();
    
    if(dlsym_error){
	_error = string("Cannot load symbol create_ui: ");
	_error.append(dlsym_error);
	throw _error;
    }
    
    _registerUI(create_ui());
}

bool Skaar::registerMessageAlias(string message, string alias){
    _messageAliases[message] = alias;
    return true;
}

Channel* Skaar::getActiveChannel(){
    return (Channel*)0;
}

void Skaar::startWork(){
    _ui->printline("Starting my work...", false);
}

const User* Skaar::getUser(){
    return (User*)0;
}
