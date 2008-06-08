#include "User.h"

User::User(string username, string nick, string password){
}

User::~User(){}

string User::getUsername(){
    return _username;
}

string User::getNick(){
    return _nick;
}

string User::getPrevNick(){
    return _prevNick;
}

string User::getPassword(){
    return _password;
}

// CLASS FACTORIES
extern "C" User* create(string username, string nick, string password){
    return new User(username, nick, password);
}

extern "C" void destroy(User* user){
    delete user;
}
