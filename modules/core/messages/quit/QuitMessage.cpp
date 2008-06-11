#include <stdlib.h>

#include "Message.h"

Message::Message(string raw){
    _raw	= raw;
    _init();
}

Message::~Message(){}

MessageFormat* Message::_getFormatFor(Message* m){
    for(int i = 0; i < _registeredFormats.size(); i++){
	MessageFormat* mf = _registeredFormats.at(i);
	
	if( ! m->friendly().empty() ){
	    if(mf->friendly() == m->friendly()){
		return mf;
	    }
	}else if( ! m->command().empty() ){
	    if(mf->command() == m->friendly()){
		return mf;
	    }
	}
    }
    return 0;
}

void Message::_init(){
    StringTokenizer st(_raw, ' ');
    
    if(_raw.at(0) == '/'){
	_initUserMessage(st);
    }else if(_raw.at(0) == ':'){
	_initPrefixMessage(st); 
    }else{
	_initNonPrefixMessage(st);
    }
}

void Message::_initUserMessage(StringTokenizer st){
    /*
     * Message needs to be translated from
     * a user-entered format.
     */
    string _tmp("");
	
    // Set the friendly command
    _friendly = string(st.next()).substr(1);
    
    // Check if the message is registered
    MessageFormat* mf = _getFormatFor(this);
    
    if(mf == 0){
	throw "Unregistered message: " + _friendly + ".";
    }else{
	_minparams 	= mf->minParams();
	_command 	= mf->command();
    }
    
    // Insert the parameter(s)
    while(st.hasNext()){
	_tmp = string(st.next());
	
	if(_tmp.at(0) == ':'){
	    _tmp = _tmp.substr(1);
	    
	    while(st.hasNext()){
		_tmp = _tmp.append(" ");
		_tmp = _tmp.append(st.next());
	    }
	    _params.push_back(_tmp);
	    
	    break;
	}else{
	    _params.push_back(_tmp);
	}
    }
	
    // Check for the minimum amount of params
    if(_params.size() < _minparams){
	throw "You supplied not enough parameters (" + string(itoa(_params.size())) + "), I expected at least " + string(itoa(_minparams)) + ".";
    }
}

void Message::_initPrefixMessage(Stringtokenizer st){
    
    if( ! st.hasNext()){
	throw "Message contains nog enough parameters!";
    }
	
    string _tmp = string(st.next());
    _prefix = _tmp.substr(1);
    _command = string(st.next());
	
    while(st.hasNext()){
	_tmp = string(st.next());
	    
	if(_tmp.at(0) == ':'){
	    /*
	     * If the token starts with ':', 
	     * the following tokens all belong to 
	     * the current parameter.
	     */
	    _tmp = _tmp.substr(1);
		
	    while(st.hasNext()){
		_tmp = _tmp.append(" ");
		_tmp = _tmp.append(st.next()); 
	    }
	    _params.push_back(_tmp);
		
	    // Stop looping
	    break;
	}else{
	    _params.push_back(_tmp);
	}
    } // while(st.hasNext())	
}

void Message::_initNonPrefixMessage(StringTokenizer st){
    throw "Not yet implemented";
}


string Message::translate(){
    string _tmp("");
    
    if( ! _prefix.empty()){
	_tmp = _tmp.append(":");
	_tmp = _tmp.append(_prefix);
    }
    
    _tmp = _tmp.append(" ");
    _tmp = _tmp.append(_command);
    
    for(int i = 0; i < _params.size(); i++){
	string _param = _params.at(i);
	
    return _command + string(" :Leaving") + string(CRLF);
}

const string Message::prefix(){
    return _prefix;
}

const string Message::command(){
    return _command;
}

const string Message::friendly(){
    return _friendly;
}

const vector<string> Message::params(){
    return _params;
}

const unsigned int Message::minParams(){
    return _minparams;
}

bool Message::setUser(User* user){
    _user = user;
    return true;
}	

bool Message::setChannel(Channel* channel){
    _channel = channel;
    return true;
}

bool Message::transmit(IRCConnection* conn){
    if(conn != 0){
	return conn->sendMessage(translate());
    }else{
	throw "No connection available!";
    }
}

void Message::registerFormat(MessageFormat* mf){
    for(int i = 0; i < _registeredFormats.size(); i++){
	MessageFormat* _tmp = _registeredFormats.at(i);
	if(mf->friendly() == _tmp->friendly() ){
	    throw "A format is already registered for friendly " + mf->friendly() ".";
	}
	if(mf == _tmp){
	    throw "This format is already registered."
	}
    }
    
    _registeredFormats.push_back(mf);    
}

void Message::unregisterFormat(MessageFormat* mf){
    vector<MessageFormat*>::iterator iter;
    
    for(iter = _registeredFormats.begin(); iter != _registeredFormats.end(); iter++){
	if(mf == iter){
	    _registeredFormats.erase(iter);
	}
    }
}

bool Message::isRegistered(Message* m){
    return (_getFormatFor(m) != 0);
}

extern "C" Message* create_message(string raw){
    return new Message(raw);
}

extern "C" void destroy_message(Message* message){
    delete message;
}
