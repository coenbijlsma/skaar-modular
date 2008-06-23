#include "AdminMessage.h"
#include "StringTokenizer.h"

/* Constructor */
AdminMessage::AdminMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
AdminMessage::~AdminMessage(){}

/* Initializes the message */
void AdminMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (ADMINMESSAGE_MINPARAMS +1) ||  st.count() > (ADMINMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != ADMINMESSAGE_COMMAND){
	throw string("Not a ") + string(ADMINMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string AdminMessage::translate(){
    
    string _tmp;
    _tmp.append(ADMINMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string AdminMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> AdminMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void AdminMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool AdminMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string AdminMessage::command(){
    return ADMINMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int AdminMessage::minParams(){
    return ADMINMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" AdminMessage* create_adminmessage(string raw){
    return new AdminMessage(raw);
}

extern "C" void destroy_adminmessage(AdminMessage* message){
    delete message;
}
