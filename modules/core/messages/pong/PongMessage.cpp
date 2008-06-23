#include "PongMessage.h"
#include "StringTokenizer.h"

/* Constructor */
PongMessage::PongMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
PongMessage::~PongMessage(){}

/* Initializes the message */
void PongMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (PONGMESSAGE_MINPARAMS +1) || st.count() > (PONGMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != PONGMESSAGE_COMMAND){
	throw string("Not a ") + string(PONGMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string PongMessage::translate(){
    
    string _tmp;
    _tmp.append(PONGMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string PongMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> PongMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void PongMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool PongMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string PongMessage::command(){
    return PONGMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int PongMessage::minParams(){
    return PONGMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" PongMessage* create_pongmessage(string raw){
    return new PongMessage(raw);
}

extern "C" void destroy_pongmessage(PongMessage* message){
    delete message;
}
