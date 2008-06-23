#include "ModeMessage.h"
#include "StringTokenizer.h"

/* Constructor */
ModeMessage::ModeMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
ModeMessage::~ModeMessage(){}

/* Initializes the message */
void ModeMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (MODEMESSAGE_MINPARAMS +1) || st.count() > (MODEMESSAGE_MAXPARAMS +1)){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != MODEMESSAGE_COMMAND){
	throw string("Not a ") + string(MODEMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string ModeMessage::translate(){
    
    string _tmp;
    _tmp.append(MODEMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
const string ModeMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
const vector<string> ModeMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void ModeMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool ModeMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
const string ModeMessage::command(){
    return MODEMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
const unsigned int ModeMessage::minParams(){
    return MODEMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" ModeMessage* create_modemessage(string raw){
    return new ModeMessage(raw);
}

extern "C" void destroy_modemessage(ModeMessage* message){
    delete message;
}
