#include "NamesMessage.h"
#include "StringTokenizer.h"

/* Constructor */
NamesMessage::NamesMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
NamesMessage::~NamesMessage(){}

/* Initializes the message */
void NamesMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (NAMESMESSAGE_MINPARAMS +1) || st.count() > (NAMESMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a names message */
    if(string(st.next()).substr(1) != NAMESMESSAGE_COMMAND){
	throw string("Not a ") + string(NAMESMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string NamesMessage::translate(){
    
    string _tmp;
    _tmp.append(NAMESMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string NamesMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> NamesMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void NamesMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool NamesMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string NamesMessage::command(){
    return NAMESMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int NamesMessage::minParams(){
    return NAMESMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" NamesMessage* create_namesmessage(string raw){
    return new NamesMessage(raw);
}

extern "C" void destroy_namesmessage(NamesMessage* message){
    delete message;
}
