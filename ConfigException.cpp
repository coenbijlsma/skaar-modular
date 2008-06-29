#include "ConfigException.h"

ConfigException::ConfigException(const char* what) throw(){
    _what = what;
}

ConfigException::~ConfigException() throw(){}

const char* ConfigException::what() const throw(){
    return _what;
}
