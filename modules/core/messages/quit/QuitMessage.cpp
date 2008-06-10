#include "QuitMessage.h"

QuitMessage::QuitMessage(string raw){
    _raw = raw;
    _init();
}

QuitMessage::~QuitMessage(){}

void QuitMessage::_init(){
    if(_raw.at(0) == '/'){
	StringTokenizer st(_raw, ' ');
	string prm("");
	
	// Set the command
	_command = string(st.next()).substr(1);
	    
	// Insert the parameter
	while(st.hasNext()){
	    prm = prm + st.next() + ' ';
	}
	
	_params.push_back(prm);
	    
    }else{
	throw "Invalid message: " + _raw;
    }
}

string QuitMessage::translate(){
    if(_params.size() > 0){
	return "QUIT :" + _params.at(0) + CRLF;
    }
    
    return string("QUIT :Leaving") + string(CRLF);
}

const string QuitMessage::command(){
    return _command;
}

const vector<string> QuitMessage::params(){
    return _params;
}

bool QuitMessage::setUser(User* user){
    _user = user;
    return true;
}	

bool QuitMessage::setChannel(Channel* channel){
    _channel = channel;
    return true;
}

bool QuitMessage::transmit(IRCConnection* conn){
    return conn->sendMessage(translate());
}

bool QuitMessage::reInit(string raw){
    _raw = raw;
    
    try{
        _init();
	return true;
    }catch(string msg){
	/* XXX Replace by logging */
	cerr << "ERROR: " << msg << endl;
	return false;
    }
}


extern "C" QuitMessage* create_qmessage(string raw){
    return new QuitMessage(raw);
}

extern "C" void destroy_qmessage(QuitMessage* message){
    delete message;
}
