#include "Channel.h"

Channel::Channel(string name){
    if(name == NULL){
	throw "A channelname cannot be NULL\n";
    }
    _name = name;
}

Channel::~Channel(){}

string Channel::getName(){
    return _name;
}
