#include "TraceMessage.h"
#include "StringTokenizer.h"

/* Constructor */
TraceMessage::TraceMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
TraceMessage::~TraceMessage(){}

/* Initializes the message */
void TraceMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (TRACEMESSAGE_MINPARAMS +1) ||  st.count() > (TRACEMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != TRACEMESSAGE_COMMAND){
	throw string("Not a ") + string(TRACEMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string TraceMessage::translate(){
    
    string _tmp;
    _tmp.append(TRACEMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string TraceMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> TraceMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void TraceMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool TraceMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string TraceMessage::command(){
    return TRACEMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int TraceMessage::minParams(){
    return TRACEMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" TraceMessage* create_tracemessage(string raw){
    return new TraceMessage(raw);
}

extern "C" void destroy_tracemessage(TraceMessage* message){
    delete message;
}
