#include "InfoMessage.h"
#include "StringTokenizer.h"

/* Constructor */
InfoMessage::InfoMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
InfoMessage::~InfoMessage(){}

/* Initializes the message */
void InfoMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (INFOMESSAGE_MINPARAMS +1) ||  st.count() > (INFOMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != INFOMESSAGE_COMMAND){
	throw string("Not a ") + string(INFOMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string InfoMessage::translate(){
    
    string _tmp;
    _tmp.append(INFOMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string InfoMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> InfoMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void InfoMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool InfoMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string InfoMessage::command(){
    return INFOMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int InfoMessage::minParams(){
    return INFOMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" InfoMessage* create_infomessage(string raw){
    return new InfoMessage(raw);
}

extern "C" void destroy_infomessage(InfoMessage* message){
    delete message;
}
