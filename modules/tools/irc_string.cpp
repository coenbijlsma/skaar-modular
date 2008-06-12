#include "irc_string.h"

irc_string::irc_string(){
    _original 	= string("");
    _work 	= _deepcopy(_original);
}

irc_string::irc_string(const string s){
    _original	= s;
    _work 	= _deepcopy(s);
}

irc_string::~irc_string(){
    delete _work;
}

string irc_string::cpp_string(){
    return _work;
}

string irc_string::_deepcopy(const string s){
    string _temp;
    for(int i = 0; i < s.size(); i ++){
	_temp.append(s.at(i));
    }
}
