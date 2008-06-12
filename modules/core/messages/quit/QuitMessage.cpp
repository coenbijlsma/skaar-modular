#include <stdlib.h>

#include "QuitMessage.h"

QuitMessage::QuitMessage(string raw){
    _raw  = raw;
    _init();
}

QuitMessage::~QuitMessage(){}

void QuitMessage::_init(){
    StringTokenizer st(_raw, ' ');
    
    if(_raw.at(0) == '/'){
	_initFriendlyMessage(st);
    }else if(_raw.at(0) == ':'){
	_initMessage(st); 
    }
}

void QuitMessage::_initFriendlyMessage(StringTokenizer st){
    /*
     * Message needs to be translated from
     * a user-entered format.
     */
    string _tmp("");
	
    // Set the friendly command
    _friendly = string(st.next()).substr(1);
    
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
	
}

void QuitMessage::_initMessage(StringTokenizer st){
    
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

string QuitMessage::translate(){
    string _tmp("");
    
    if( ! _prefix.empty()){
	_tmp = _tmp.append(":");
	_tmp = _tmp.append(_prefix);
    }
    
    _tmp = _tmp.append(" ");
    _tmp = _tmp.append(_command);
    
    for(int i = 0; i < _params.size(); i++){
	string _param = _params.at(i);
    }
    	
    return _command + string(" :Leaving") + string(CRLF);
}

const string QuitMessage::prefix(){
    return _prefix;
}

const string QuitMessage::command(){
    return _command;
}

const string QuitMessage::friendly(){
    return _friendly;
}

const vector<string> QuitMessage::params(){
    return _params;
}

const unsigned int QuitMessage::minParams(){
    return _minparams;
}

bool QuitMessage::setUser(User* user){
    _user = user;
    return true;
}	

bool QuitMessage::transmit(IRCConnection* conn){
    if(conn != 0){
	return conn->sendMessage(translate());
    }else{
	throw "No connection available!";
    }
}

extern "C" QuitMessage* create_qmessage(string raw){
    return new QuitMessage(raw);
}

extern "C" void destroy_qmessage(QuitMessage* message){
    delete message;
}
