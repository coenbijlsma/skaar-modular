#include "Skaar.h"

#include <dlfcn.h> // libraries

/* Registers the UI to print output to */
bool Skaar::_registerUI(VirtualUI* ui){
    if(_ui == 0 && ui != 0){
	_ui = ui;
	return true;
    }
    return false;
}

/* Initializes the UI */
void Skaar::_initUI(){
    /* Initialize the UI */
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

/* Destroys the UI */
void Skaar::_destroyUI(VirtualUI* ui){
    if( ui != 0){
	destroy_ui_t* destroy_ui = (destroy_ui_t*) dlsym(_dlUI, "destroy_ui");
	const char* dlsym_error = dlerror();
	
	if(dlsym_error){
	    cerr << "Could not load symbol destroy_ui: " << dlsym_error << endl;
	    delete ui;
	    return;
	}
	
	destroy_ui(ui);
	dlclose(_dlUI);
    }
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

/* Registers the message aliases */
void Skaar::_registerMessageAliases(){
    SkaarConfigSection* _aliasSection = _config->getSection("aliases");
    
    if(_aliasSection != 0){
	map<string, string> _aliases = _aliasSection->all();
	map<string, string>::iterator _iter;
	
	for(_iter = _aliases.begin(); _iter != _aliases.end(); _iter++){
	    if( ! registerMessageAlias( (*_iter).second, (*_iter).first )){
		string _logString("Registering message alias failed: ");
		_logString.append((*_iter).second);
		_logString.append("(");
		_logString.append((*_iter).first);
		_logString.append(")");
		
		_log->append(_logString, SkaarLog::LOG_ERROR, true);
	    }
	}
	
    }
}

/* Registers the user to skaar */
bool Skaar::_setUser(User* user){
    if(_user == 0){
	if( user != 0 ){
	    _user = user;
	    return true;
	}
    }
    return false;
}

/* Registers the user to the server */
bool Skaar::_registerAt(IRCConnection* conn){
    int _strlen = (*iter).first.size();
    char* _server = new char[_strlen +1];
    strcpy(_server, (*iter).first.c_str());
	    
    IRCConnection* _connection = new IRCConnection( _server, _port );
    if(_connection->createConnection()){
	/* Log on to irc */
	string _spassmsg("/PASS ");
	_spassmsg.append(_user->getPassword());
		
	PassMessage* _passmsg = new PassMessage(_spassmsg);
		
	if( ! _passmsg->transmit(_connection) ){
	    throw "Could not send PASS message!";
	}
		
	string _snickmsg("/NICK ");
	_snickmsg.append(_user->getNick());
		
	NickMessage* _nickmsg = new NickMessage(_snickmsg);
		
	if( ! _nickmsg->transmit(_connection) ){
	    throw "Could not send NICK message!";
	}
		
	string _susermsg("/USER ");
	_susermsg.append(_user->getNick());
	_susermsg.append(" localhost ");
	_susermsg.append("foo ");
	_susermsg.append(_user->getUsername());
		
	UserMessage* _usermsg = new UserMessage(_susermsg);
		
	if( ! _usermsg->transmit(_connection) ){
	    throw "Could not send USER message!";
	}
		
	/* Store the connection */
	_connections.push_back(_connection);
	
	/* Clean up */
	delete _server;
	return true;
    }else{
	/* Clean up */
	delete _server;
	delete _connection;
	return false;
    }
}

/* Constructor */
Skaar::Skaar(){
    string _tmparray[] = {"PASS", "NICK", "USER", "OPER", "QUIT",
		"JOIN", "PART", "MODE", "TOPIC", "NAMES",
		"LIST", "INVITE", "KICK", "VERSION", "STATS",
		"LINKS", "TRACE", "ADMIN", "INFO", "PRIVMSG",
		"NOTICE", "WHO", "WHOIS", "WHOWAS", "PONG",
		""};
    
    //cout << "Messages 1" << endl;
    
    for(int i = 0; i < MESSAGECOUNT; i++){
	_messages[i] = _tmparray[i];
    }
    
    //cout << "Messages loop" << endl;
}

/* Destructor */
Skaar::~Skaar(){
    /* Clean up all the channels */
    _openChannels.clear();
        
    /* Disconnect from all servers and clean up */
    _connections.clear();
    
    delete _config;
    delete _user;
    
    _destroyUI(_ui);
}

/* Initializes Skaar */
void Skaar::init(){
    /* Initialize logging */
    _log = new SkaarLog("skaar.log");
    
    /* Read the config */
    _config = new SkaarConfig();
    
    /* Initialize the UI */
    _initUI();
    
    /* Register the messages */
    for(int i = 0; i < MESSAGECOUNT; i++){
	_registerMessage(_messages[i]);
    }
    
    /* Register the message aliases */
    _registerMessageAliases();
    cout << "Init done" << endl;
}

/* Registers an alias for a message */
bool Skaar::registerMessageAlias(string message, string alias){
    bool _found = false;
    for(int i = 0; i < MESSAGECOUNT; i++){
	if(_messages[i] == message){
	    _found = true;
	    break;
	}
    }
    
    /* Do nothing if the message wasn't found */
    if( ! _found){
	return false;
    }
    
    _messageAliases[message] = alias;
    return true;
}

Channel* Skaar::getActiveChannel(){
    return (Channel*)0;
}

void Skaar::startWork(){
    _ui->printline("Starting the works...", false);
    
    /* XXX Create windows for each connection and channel */
    SkaarConfigSection* _servers = _config->getSection("servers");
    SkaarConfigSection* _core = _config->getSection("core");
    
    if(_core == 0){
	throw "Core section not found!";
    }
    //cout << "Sections read" << endl;
    
    string _username = _core->get("realname");
    string _nick = _core->get("nick");
    string _password = _core->get("password");
    
    if(_username.empty() || _nick.empty() || _password.empty() ){
	/* Read the user data */
	_ui->printline("Not enough data to register you.");
	_ui->printline("Enter your name (e.g. Mister foo):");
	_username = _ui->readline();
	
	_ui->printline("Enter your nickname (e.g. bar)");
	_nick = _ui->readline();
	
	_ui->printline("Enter your password:");
	_password = _ui->readline();
	
	/* And store it in the settings */
	_core->set("realname", _username);
	_core->set("nick", _nick);
	_core->set("password", _password);
    }
    
    if( ! _setUser(new User(_username, _nick, _password))){
	throw "No user available!";
    }
    
    /* Connect to the servers if any */
    if(_servers != 0){
	map<string, string> _allServers = _servers->all();
	for(map<string, string>::iterator iter = _allServers.begin(); iter != _allServers.end(); iter++){
	    string _server( iter->first );
	    istringstream _buf( iter->second );
	    int _port;
	    _buf >> _port;
	    
	    /* Register the user at the server */
	    _registerAt(_server, _port);	    
	}
    }
    	
    /* XXX FIXME this while(1) */
    while(1){
	for(int i = 0; i < _connections.size(); i++){
	    IRCConnection* _tconn = _connections.at(i);
	    if(_tconn->pollConnection() > 0){
		/* Do something */
		char* _tmp = _tconn->readMessage();

		if(_tmp != 0 && _tmp != CRLF){
		    string s(_tmp);
		    GenericMessage* _gm = new GenericMessage(s);
		    string _tstr = _gm->translate();
		    if( (! _tstr.empty()) &&  _tstr.c_str() != 0 ){
			_ui->print( _tstr, false);
		    } // _tstr.empty() ...

		} // _tmp != 0 ...
		
	    } // _tconn->pollConnection() > 0
	    
	} // for( ...; connections.size(); ...)
	
    } // while(1) XXX
}

/* Returns the user */
const User* Skaar::getUser(){
    return (User*)0;
}
