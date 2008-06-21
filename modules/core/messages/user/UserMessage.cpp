#include "UserMessage.h"
#include "StringTokenizer.h"

/* Constructor */
UserMessage::UserMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
UserMessage::~UserMessage(){}

/* Initializes the message */
void UserMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (USERMESSAGE_MINPARAMS +1) ){
	throw string("Not enough parameters supplied in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    // XXX ALIASES
    if(string(st.next()).substr(1) != USERMESSAGE_COMMAND){
	throw string("Not a ") + string(USERMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	/* If we reach the last parameter, put them together */
	if(i == (USERMESSAGE_MAXPARAMS -1)){
	    while(st.hasNext()){
		_tmp.append( _tmp.empty() ? "" : SPACE );
		_tmp.append( (string(st.next())) );
	    }
	    _params.push_back(_tmp);
	}else{    
	    _params.push_back(string(st.next()));
	}
    }
}

/* Translate the message to an RFC string */
string UserMessage::translate(){
    
    string _tmp;
    _tmp.append(USERMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append( (i == _params.size() -1) ? ":" : ""); // prepend colon for the last parameter
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
const string UserMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
const vector<string> UserMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void UserMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool UserMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
const string UserMessage::command(){
    return USERMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
const unsigned int UserMessage::minParams(){
    return USERMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" UserMessage* create_nickmessage(string raw){
    return new UserMessage(raw);
}

extern "C" void destroy_nickmessage(UserMessage* message){
    delete message;
}
