#include "WhoisMessage.h"
#include "StringTokenizer.h"

/* Constructor */
WhoisMessage::WhoisMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
WhoisMessage::~WhoisMessage(){}

/* Initializes the message */
void WhoisMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (WHOISMESSAGE_MINPARAMS +1) || st.count() > (WHOISMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != WHOISMESSAGE_COMMAND){
	throw string("Not a ") + string(WHOISMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string WhoisMessage::translate(){
    
    string _tmp;
    _tmp.append(WHOISMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string WhoisMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> WhoisMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void WhoisMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool WhoisMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string WhoisMessage::command(){
    return WHOISMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int WhoisMessage::minParams(){
    return WHOISMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" WhoisMessage* create_whoismessage(string raw){
    return new WhoisMessage(raw);
}

extern "C" void destroy_whoismessage(WhoisMessage* message){
    delete message;
}
