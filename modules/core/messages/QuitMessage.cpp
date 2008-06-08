#include "Message.h"

class QuitMessage : public Message {

public:
    QuitMessage(string raw){
	_raw = raw;
        _init();
    }

    ~QuitMessage(){}

    string translate(){
        return "";
    }

    const string command(){
        return _command;
    }

    const vector<string> params(){
        return _params;
    }

    bool setUser(User* user){
        _user = user;
	return true;
    }

    bool setChannel(Channel* channel){
        _channel = channel;
	return true;
    }

    bool transmit(IRCConnection* conn){
        // XXX
	return true;
    }

    bool reInit(string raw){
        _raw = raw;
        _init();
	return true;
    }
};

extern "C" Message* create(string raw){
    return (Message*) new QuitMessage(raw);
}

extern "C" void destroy(Message* message){
    delete message;
}

