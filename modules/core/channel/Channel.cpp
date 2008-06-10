#include "Channel.h"

Channel::Channel(string name){
    if(name.empty()){
	throw "A channelname cannot be empty.\n";
    }
    _name = name;
}

Channel::~Channel(){}

const string Channel::getName(){
    return _name;
}

extern "C" Channel* create_channel(string name){
    return new Channel(name);
}

extern "C" void destroy_channel(Channel* channel){
    delete channel;
}
