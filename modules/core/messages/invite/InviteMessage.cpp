#include "InviteMessage.h"
#include "StringTokenizer.h"

/* Constructor */
InviteMessage::InviteMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
InviteMessage::~InviteMessage(){}

/* Initializes the message */
void InviteMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (INVITEMESSAGE_MINPARAMS +1) &&  !st.count() > (INVITEMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != INVITEMESSAGE_COMMAND){
	throw string("Not a ") + string(INVITEMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string InviteMessage::translate(){
    
    string _tmp;
    _tmp.append(INVITEMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string InviteMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> InviteMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void InviteMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool InviteMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string InviteMessage::command(){
    return INVITEMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int InviteMessage::minParams(){
    return INVITEMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" InviteMessage* create_invitemessage(string raw){
    return new InviteMessage(raw);
}

extern "C" void destroy_invitemessage(InviteMessage* message){
    delete message;
}
