#include "StatsMessage.h"
#include "StringTokenizer.h"

/* Constructor */
StatsMessage::StatsMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
StatsMessage::~StatsMessage(){}

/* Initializes the message */
void StatsMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (STATSMESSAGE_MINPARAMS +1) || st.count() > (STATSMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != STATSMESSAGE_COMMAND){
	throw string("Not a ") + string(STATSMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	string _token = string(st.next());
	if( i == 0 ){
	    for(int j = 0; j < _token.size(); j++){
		bool _legal = false;
		for(int n = 0; n < ALLOWED_QUERIES.size(); n++){
		    if(_token.at(j) == ALLOWED_QUERIES.at(n)){
			_legal = true;
		    }
		}
		
		if( ! _legal ){
		    string _message("Illegal query in message ");
		    _message.append(_raw);
		    throw _message;
		}
	    }
	}
	
	_params.push_back(_token);	    
    }
}

/* Translate the message to an RFC string */
string StatsMessage::translate(){
    
    string _tmp;
    _tmp.append(STATSMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string StatsMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> StatsMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void StatsMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool StatsMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string StatsMessage::command(){
    return STATSMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int StatsMessage::minParams(){
    return STATSMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" StatsMessage* create_statsmessage(string raw){
    return new StatsMessage(raw);
}

extern "C" void destroy_statsmessage(StatsMessage* message){
    delete message;
}
