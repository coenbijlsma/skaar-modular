#include "QuitMessage.h"

QuitMessage::QuitMessage(string raw){
    _raw = raw;
    _init();
}

QuitMessage::~QuitMessage(){}

string QuitMessage::translate(){
    return "";
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
    // XXX
    return true;
}

bool QuitMessage::reInit(string raw){
    _raw = raw;
    _init();
    return true;
}


extern "C" QuitMessage* create_qmessage(string raw){
    return new QuitMessage(raw);
}

extern "C" void destroy_qmessage(QuitMessage* message){
    delete message;
}
