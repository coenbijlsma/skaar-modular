#include "NoticeMessage.h"
#include "StringTokenizer.h"

/* Constructor */
NoticeMessage::NoticeMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
NoticeMessage::~NoticeMessage(){}

/* Initializes the message */
void NoticeMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    
    if(st.count() < (NOTICEMESSAGE_MINPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a privmsg message */
    if(string(st.next()).substr(1) != NOTICEMESSAGE_COMMAND){
	throw string("Not a ") + string(NOTICEMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
	
    /* Read the message */
    _params.push_back(string(st.next())); // Nickname
    string _tmp;
    
    while(st.hasNext()){
	_tmp.append(_tmp.empty() ? "" : SPACE);
	_tmp.append(string(st.next()));
    }
	
    _params.push_back(_tmp);
}

/* Translate the message to an RFC string */
string NoticeMessage::translate(){
    
    string _tmp;
    _tmp.append(NOTICEMESSAGE_COMMAND);
    _tmp.append(SPACE);
    _tmp.append(_params.at(0)); // Nickname
    
    /* Add the message text */
    for(int i = 1; i < _params.size(); i++){
	
	_tmp.append(i == 1 ? " :" : SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string NoticeMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> NoticeMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void NoticeMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool NoticeMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string NoticeMessage::command(){
    return NOTICEMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int NoticeMessage::minParams(){
    return NOTICEMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" NoticeMessage* create_noticemessage(string raw){
    return new NoticeMessage(raw);
}

extern "C" void destroy_noticemessage(NoticeMessage* message){
    delete message;
}
