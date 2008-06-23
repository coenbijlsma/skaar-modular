#include "ListMessage.h"
#include "StringTokenizer.h"

/* Constructor */
ListMessage::ListMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
ListMessage::~ListMessage(){}

/* Initializes the message */
void ListMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (LISTMESSAGE_MINPARAMS +1) ){
	throw string("Not enough parameters supplied in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != LISTMESSAGE_COMMAND){
	throw string("Not a ") + string(LISTMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string ListMessage::translate(){
    
    string _tmp;
    _tmp.append(LISTMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string ListMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> ListMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void ListMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool ListMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string ListMessage::command(){
    return LISTMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int ListMessage::minParams(){
    return LISTMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" ListMessage* create_listmessage(string raw){
    return new ListMessage(raw);
}

extern "C" void destroy_listmessage(ListMessage* message){
    delete message;
}
