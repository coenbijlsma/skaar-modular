#include "TopicMessage.h"
#include "StringTokenizer.h"

/* Constructor */
TopicMessage::TopicMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
TopicMessage::~TopicMessage(){}

/* Initializes the message */
void TopicMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (TOPICMESSAGE_MINPARAMS +1) ){
	throw string("Not enough parameters supplied in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != TOPICMESSAGE_COMMAND){
	throw string("Not a ") + string(TOPICMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	/* If we reach the last parameter, put them together */
	if(i == (TOPICMESSAGE_MAXPARAMS -1)){
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
string TopicMessage::translate(){
    
    string _tmp;
    _tmp.append(TOPICMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append( (i == _params.size() -1) ? ":" : ""); // prepend colon for the last parameter
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string TopicMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> TopicMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void TopicMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool TopicMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string TopicMessage::command(){
    return TOPICMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int TopicMessage::minParams(){
    return TOPICMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" TopicMessage* create_topicmessage(string raw){
    return new TopicMessage(raw);
}

extern "C" void destroy_topicmessage(TopicMessage* message){
    delete message;
}
