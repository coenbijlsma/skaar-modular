#include "OperMessage.h"
#include "StringTokenizer.h"

/* Constructor */
OperMessage::OperMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
OperMessage::~OperMessage(){}

/* Initializes the message */
void OperMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (OPERMESSAGE_MINPARAMS +1) ){
	throw string("Not enough parameters supplied in message ") + _raw;
    }
    
    /* Check if the message really is a oper message */
    // XXX ALIASES
    if(string(st.next()).substr(1) != OPERMESSAGE_COMMAND){
	throw string("Not a ") + string(OPERMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string OperMessage::translate(){
    
    string _tmp;
    _tmp.append(OPERMESSAGE_COMMAND);

    if(_params.size() == 0){ // Use the username and password from the config file
	if(_user == 0){
	    throw "Not enough parameters supplied: need username and password.";
	}
	
	_params.push_back(_user->getNick());
	_params.push_back(_user->getPassword());
    }else if(_params.size() == 1){ // Assume that no username was supplied
	if(_user == 0){
	    throw "Not enough parameters supplied: need an username.";
	}
	
	_params.insert(_params.begin(), 1, _user->getNick());
    }
    
    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
const string OperMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
const vector<string> OperMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void OperMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool OperMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
const string OperMessage::command(){
    return OPERMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
const unsigned int OperMessage::minParams(){
    return OPERMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" OperMessage* create_nickmessage(string raw){
    return new OperMessage(raw);
}

extern "C" void destroy_nickmessage(OperMessage* message){
    delete message;
}
