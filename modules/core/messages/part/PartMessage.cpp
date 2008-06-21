#include "PartMessage.h"
#include "StringTokenizer.h"

/* Constructor */
PartMessage::PartMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
PartMessage::~PartMessage(){}

/* Initializes the message */
void PartMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() != (PARTMESSAGE_MINPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a part message */
    if(string(st.next()).substr(1) != PARTMESSAGE_COMMAND){
	throw string("Not a ") + string(PARTMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string PartMessage::translate(){
    
    string _tmp;
    _tmp.append(PARTMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string PartMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> PartMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void PartMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool PartMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string PartMessage::command(){
    return PARTMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
const unsigned int PartMessage::minParams(){
    return PARTMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" PartMessage* create_partmessage(string raw){
    return new PartMessage(raw);
}

extern "C" void destroy_partmessage(PartMessage* message){
    delete message;
}
