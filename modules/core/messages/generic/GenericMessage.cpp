#include "GenericMessage.h"
#include "StringTokenizer.h"

GenericMessage::GenericMessage(string raw){
    _raw = raw;
    _init();
}

GenericMessage::~GenericMessage(){}

void GenericMessage::_init(){
    if(_raw.empty()){
	throw "Illegal message.";
    }
    
    /* Remove the trailing CRLF */
    string::size_type loc = _raw.find(CRLF, 0);
    if(loc != string::npos){
	_raw = _raw.erase(loc);
    }
    
    StringTokenizer st(_raw, ' ');
    
    /* Check if the message contains a prefix */
    if(_raw.at(0) == ':'){
	_prefix = string(st.next()).substr(1);
    }
    
    /* Save the command */
    _command = string(st.next());
    
    /* Read the parameters */
    while(st.hasNext()){
	string next = st.next();
	
	if( ! next.at(0) == ':'){
	    _params.push_back(next);
	}else{
	    while(st.hasNext()){
		next.append(" ");
		next.append(st.next());
	    }
	    _params.push_back(next);
	}	
    }
    
}

string GenericMessage::translate(){
    string _tmp(_prefix);
    _tmp.append(" ");
    _tmp.append(_command);
    
    if(_params.size() >0){
	for(int i = 0; i < _params.size(); i++){
	    _tmp.append(" ");
	    _tmp.append(_params.at(i));
	}
    }
    return _tmp;
    
}

const string GenericMessage::prefix(){
    return _prefix;
}

const string GenericMessage::command(){
    return _command;
}

const vector<string> GenericMessage::params(){
    return _params;
}

extern "C" GenericMessage* create_genericmessage(string raw){
    return new GenericMessage(raw);
}

extern "C" void destroy_genericmessage(GenericMessage* msg){
    delete msg;
}
