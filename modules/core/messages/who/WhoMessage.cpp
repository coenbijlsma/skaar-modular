#include "WhoMessage.h"
#include "StringTokenizer.h"

/* Constructor */
WhoMessage::WhoMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
WhoMessage::~WhoMessage(){}

/* Initializes the message */
void WhoMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (WHOMESSAGE_MINPARAMS +1) || st.count() > (WHOMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != WHOMESSAGE_COMMAND){
	throw string("Not a ") + string(WHOMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string WhoMessage::translate(){
    
    string _tmp;
    _tmp.append(WHOMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string WhoMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> WhoMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void WhoMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool WhoMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string WhoMessage::command(){
    return WHOMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int WhoMessage::minParams(){
    return WHOMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" WhoMessage* create_whomessage(string raw){
    return new WhoMessage(raw);
}

extern "C" void destroy_whomessage(WhoMessage* message){
    delete message;
}
