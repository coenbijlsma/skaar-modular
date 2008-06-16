#include "PrivmsgMessage.h"
#include "StringTokenizer.h"

/* Constructor */
PrivmsgMessage::PrivmsgMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
PrivmsgMessage::~PrivmsgMessage(){}

/* Initializes the message */
void PrivmsgMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    
    if(_raw.at(0) == '/'){
	string _tmp;
	if(st.count() < (PRIVMSGMESSAGE_MINPARAMS +1) ){
	    throw string("Wrong parameter count in message ") + _raw;
	}
    
	/* Check if the message really is a privmsg message */
	// XXX ALIASES
	if(string(st.next()).substr(1) != PRIVMSGMESSAGE_COMMAND){
	    throw string("Not a ") + string(PRIVMSGMESSAGE_COMMAND) + string(" message: ") + _raw;
	}
	
	/* Read the message */
	while(st.hasNext()){
	    _tmp.append(_tmp.empty() ? "" : SPACE);
	    _tmp.append(string(st.next()));
	}
	
	_params.push_back(_tmp);
    }else{
	_params.push_back(_raw);
    }
}

/* Translate the message to an RFC string */
string PrivmsgMessage::translate(){
    
    string _tmp;
    _tmp.append(PRIVMSGMESSAGE_COMMAND);
    _tmp.append(SPACE);
    
    /* Add the receiver(s) */
    for(int i = 0; i < _receivers.size(); i++){
	_tmp.append( i > 0 ? "," : "" );
	_tmp.append(_receivers.at(i));
    }
    
    /* Add the message text */
    for(int i = 0; i < _params.size(); i++){
	_tmp.append(i == 0 ? " :" : SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
const string PrivmsgMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
const vector<string> PrivmsgMessage::params(){
    return _params;
}

const string PrivmsgMessage::receiver(){
    return _receiver;
}

/* Sets the user that sends this message */
void PrivmsgMessage::setUser(User* user){
    _user = user;
}

void PrivmsgMessage::setReceiver(string recv){
    _receiver = recv;
}

/* Transmits the message to the server */
bool PrivmsgMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
const string PrivmsgMessage::command(){
    return PRIVMSGMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
const unsigned int PrivmsgMessage::minParams(){
    return PRIVMSGMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" PrivmsgMessage* create_nickmessage(string raw){
    return new PrivmsgMessage(raw);
}

extern "C" void destroy_nickmessage(PrivmsgMessage* message){
    delete message;
}
