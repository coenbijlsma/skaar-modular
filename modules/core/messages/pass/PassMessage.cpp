#include <stdlib.h>

#include "PassMessage.h"
#include "StringTokenizer.h"

/* Constructor */
PassMessage::PassMessage(string raw){
    _raw  = raw;
    _init();
}

/* Destructor */
PassMessage::~PassMessage(){}

/* Initialize the message */
void PassMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (PASSMESSAGE_MINPARAMS +1) || st.count() > (PASSMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count for message ") + _raw;
    }
    
    /* Check if the used message is indeed a PASS message */
    // XXX ALIASES
    if( string(st.next()).substr(1) != PASSMESSAGE_FRIENDLY ){
	throw string("Not a ") + string(PASSMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Figure out the parameter(s) */
    if(st.hasNext()){
	for(int i = 0; st.hasNext(); i++){
	    _tmp.append( i == 0 ? "" : SPACE);
	    _tmp.append(string(st.next()));
	}
    }
    
    /* Store the parameter(s) */
    _params.push_back(_tmp);
    
}

string PassMessage::translate(){
    string _tmp;
    
    _tmp = _tmp.append(PASSMESSAGE_COMMAND);
    _tmp = _tmp.append(" :");
    _tmp = _tmp.append(_params.at(0));
    _tmp = _tmp.append(CRLF);
    
    return _tmp;
}

const string PassMessage::prefix(){
    // NOT IMPLEMENTED;
    return "";
}

const vector<string> PassMessage::params(){
    return _params;
}

void PassMessage::setUser(User* user){
    _user = user;
}	

bool PassMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    
    return conn->sendMessage(translate());
}

const string PassMessage::command(){
    return PASSMESSAGE_COMMAND;
}

const string PassMessage::friendly(){
    return PASSMESSAGE_FRIENDLY;
}

const unsigned int PassMessage::minParams(){
    return PASSMESSAGE_MINPARAMS;
}


////////////////////////////////////////////////////////////////////////////////
//			    CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" PassMessage* create_qmessage(string raw){
    return new PassMessage(raw);
}

extern "C" void destroy_qmessage(PassMessage* message){
    delete message;
}
