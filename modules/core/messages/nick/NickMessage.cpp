#include "NickMessage.h"
#include "StringTokenizer.h"

/* Constructor */
NickMessage::NickMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
NickMessage::~NickMessage(){}

/* Initializes the message */
void NickMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (NICKMESSAGE_MINPARAMS +1) || st.count() > (NICKMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a nick message */
    // XXX ALIASES
    if(string(st.next()).substr(1) != NICKMESSAGE_FRIENDLY){
	throw string("Not a ") + string(NICKMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string NickMessage::translate(){
    
    string _tmp;
    _tmp.append(NICKMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
const string NickMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
const vector<string> NickMessage::params(){
}

/* Sets the user that sends this message */
void NickMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool NickMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
const string NickMessage::command(){
    return NICKMESSAGE_COMMAND;
}

/* Returns the friendly command */
const string NickMessage::friendly(){
    return NICKMESSAGE_FRIENDLY;
}

/* Returns the minimum amount of parameters needed */
const unsigned int NickMessage::minParams(){
    return NICKMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" NickMessage* create_nickmessage(string raw){
    return new NickMessage(raw);
}

extern "C" void destroy_nickmessage(NickMessage* message){
    delete message;
}
