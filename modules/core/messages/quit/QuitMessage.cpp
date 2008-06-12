#include <stdlib.h>

#include "QuitMessage.h"

/* Constructor */
QuitMessage::QuitMessage(string raw){
    _raw  = raw;
    _init();
}

/* Destructor */
QuitMessage::~QuitMessage(){}

/* Initialize the message */
void QuitMessage::_init(){
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    /* Check if the message even has content */
    if(st.count() <= 1){
	throw string("Illegal message: ") + _raw;
    }
    
    /* Check if the used message is indeed a QUIT message */
    if( string(st.next()).substr(1) != "quit" ){
	throw string("Not a ") + string(QUITMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Figure out the parameter(s) */
    if(st.hasNext()){
	for(int i = 0; st.hasNext(); i++){
	    _tmp.append( i == 0 ? "" : " ");
	    _tmp.append(string(st.next()));
	}
    }else{
	_tmp.append("I am leaving");
    }
    
    /* Store the parameter(s) */
    _params.push_back(_tmp);
    
}

string QuitMessage::translate(){
    string _tmp;
    
    _tmp = _tmp.append(QUITMESSAGE_COMMAND);
    _tmp = _tmp.append(" :");
    _tmp = _tmp.append(_params.at(0));
    _tmp = _tmp.append(CRLF);
    
    return _tmp;
}

const string QuitMessage::prefix(){
    // NOT IMPLEMENTED;
    return "";
}

const vector<string> QuitMessage::params(){
    return _params;
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

////////////////////////////////////////////////////////////////////////////////
//				CONST METHODS				      //
////////////////////////////////////////////////////////////////////////////////

const string QuitMessage::command(){
    return QUITMESSAGE_COMMAND;
}

const string QuitMessage::friendly(){
    return QUITMESSAGE_FRIENDLY;
}

const unsigned int QuitMessage::minParams(){
    return QUITMESSAGE_MINPARAMS;
}


////////////////////////////////////////////////////////////////////////////////
//			    CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" QuitMessage* create_qmessage(string raw){
    return new QuitMessage(raw);
}

extern "C" void destroy_qmessage(QuitMessage* message){
    delete message;
}
