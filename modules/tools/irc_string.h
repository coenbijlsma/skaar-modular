#ifndef IRCSTRING_H
#define IRCSTRING_H

#include <string>

class irc_string {
private:
    const string 	_original;
    string		_work;
    
    string		_deepcopy(const string s);
    
public:
    irc_string();
    irc_string(const string s);
    ~irc_string();
    
    string cpp_string();
    
    irc_string operator+ (irc_string s);
    irc_string operator+ (string s);
    irc_string operator+ (char s);
    
};

#endif
