#include "WhowasMessage.h"
#include "StringTokenizer.h"

/* Constructor */
WhowasMessage::WhowasMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
WhowasMessage::~WhowasMessage(){}

/* Initializes the message */
void WhowasMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (WHOWASMESSAGE_MINPARAMS +1) || st.count() > (WHOWASMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != WHOWASMESSAGE_COMMAND){
	throw string("Not a ") + string(WHOWASMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string WhowasMessage::translate(){
    
    string _tmp;
    _tmp.append(WHOWASMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string WhowasMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> WhowasMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void WhowasMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool WhowasMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string WhowasMessage::command(){
    return WHOWASMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int WhowasMessage::minParams(){
    return WHOWASMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" WhowasMessage* create_whowasmessage(string raw){
    return new WhowasMessage(raw);
}

extern "C" void destroy_whowasmessage(WhowasMessage* message){
    delete message;
}
