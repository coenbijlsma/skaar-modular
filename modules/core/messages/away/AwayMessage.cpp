#include <stdlib.h>

#include "AwayMessage.h"
#include "StringTokenizer.h"

/* Constructor */
AwayMessage::AwayMessage(string raw){
    _raw  = raw;
    _init();
}

/* Destructor */
AwayMessage::~AwayMessage(){}

/* Initialize the message */
void AwayMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() > AWAYMESSAGE_MAXPARAMS){
	throw string("Too many parameters for message ") + _raw;
    }
    
    /* Check if the used message is indeed a QUIT message */
    // XXX ALIASES
    if( string(st.next()).substr(1) != AWAYMESSAGE_COMMAND ){
	throw string("Not a ") + string(AWAYMESSAGE_COMMAND) + string(" message: ") + _raw;
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

string AwayMessage::translate(){
    string _tmp;
    
    _tmp = _tmp.append(AWAYMESSAGE_COMMAND);
    _tmp = _tmp.append(" :");
    _tmp = _tmp.append(_params.at(0));
    _tmp = _tmp.append(CRLF);
    
    return _tmp;
}

const string AwayMessage::prefix(){
    // NOT IMPLEMENTED;
    return "";
}

const vector<string> AwayMessage::params(){
    return _params;
}

void AwayMessage::setUser(User* user){
    _user = user;
}	

bool AwayMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    
    return conn->sendMessage(translate());
}

const string AwayMessage::command(){
    return AWAYMESSAGE_COMMAND;
}

const unsigned int AwayMessage::minParams(){
    return AWAYMESSAGE_MINPARAMS;
}


////////////////////////////////////////////////////////////////////////////////
//			    CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" AwayMessage* create_awaymessage(string raw){
    return new AwayMessage(raw);
}

extern "C" void destroy_awaymessage(AwayMessage* message){
    delete message;
}
