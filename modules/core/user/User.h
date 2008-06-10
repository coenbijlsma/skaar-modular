#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string _username;
    string _nick;
    string _prevNick;
    string _password;
    
public:
    User(string username, string nick, string password);
    ~User();
    
    string 	getUsername();
    string 	getNick();
    string 	getPrevNick();
    string 	getPassword();
};


// CLASS FACTORIES
typedef User* create_user(string username, string nick, string password);
typedef void destroy_user(User*);

#endif
