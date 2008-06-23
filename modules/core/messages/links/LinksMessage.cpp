#include "LinksMessage.h"
#include "StringTokenizer.h"

/* Constructor */
LinksMessage::LinksMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
LinksMessage::~LinksMessage(){}

/* Initializes the message */
void LinksMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (LINKSMESSAGE_MINPARAMS +1) || st.count() > (LINKSMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != LINKSMESSAGE_COMMAND){
	throw string("Not a ") + string(LINKSMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string LinksMessage::translate(){
    
    string _tmp;
    _tmp.append(LINKSMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string LinksMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> LinksMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void LinksMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool LinksMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string LinksMessage::command(){
    return LINKSMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int LinksMessage::minParams(){
    return LINKSMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" LinksMessage* create_linksmessage(string raw){
    return new LinksMessage(raw);
}

extern "C" void destroy_linksmessage(LinksMessage* message){
    delete message;
}
