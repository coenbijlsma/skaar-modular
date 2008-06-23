#include "VersionMessage.h"
#include "StringTokenizer.h"

/* Constructor */
VersionMessage::VersionMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
VersionMessage::~VersionMessage(){}

/* Initializes the message */
void VersionMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (VERSIONMESSAGE_MINPARAMS +1) || st.count() > (VERSIONMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != VERSIONMESSAGE_COMMAND){
	throw string("Not a ") + string(VERSIONMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string VersionMessage::translate(){
    
    string _tmp;
    _tmp.append(VERSIONMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string VersionMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> VersionMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void VersionMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool VersionMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string VersionMessage::command(){
    return VERSIONMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int VersionMessage::minParams(){
    return VERSIONMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" VersionMessage* create_versionmessage(string raw){
    return new VersionMessage(raw);
}

extern "C" void destroy_versionmessage(VersionMessage* message){
    delete message;
}
