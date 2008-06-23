#include "KickMessage.h"
#include "StringTokenizer.h"

/* Constructor */
KickMessage::KickMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
KickMessage::~KickMessage(){}

/* Initializes the message */
void KickMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (KICKMESSAGE_MINPARAMS +1) ){
	throw string("Not enough parameters supplied in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != KICKMESSAGE_COMMAND){
	throw string("Not a ") + string(KICKMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	if(i == (KICKMESSAGE_MAXPARAMS -1)){
	    string _tmp;
	    
	    for(int j = i; st.hasNext(); j++){
		_tmp.append( j == i ? "" : SPACE);
		_tmp.append(st.next());
	    }
	    _params.push_back(_tmp);
	}else{
	    _params.push_back(string(st.next()));
	}
    }
}

/* Translate the message to an RFC string */
string KickMessage::translate(){
    
    string _tmp;
    _tmp.append(KICKMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(i == (KICKMESSAGE_MAXPARAMS -1) ? " :" : SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string KickMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> KickMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void KickMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool KickMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string KickMessage::command(){
    return KICKMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int KickMessage::minParams(){
    return KICKMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" KickMessage* create_kickmessage(string raw){
    return new KickMessage(raw);
}

extern "C" void destroy_kickmessage(KickMessage* message){
    delete message;
}
