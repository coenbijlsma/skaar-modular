#include "MessageException.h"

MessageException::MessageException(const char* what) throw(){
    _what = what;
}

MessageException::~MessageException() throw(){}

const char* MessageException::what() const throw(){
    return _what;
}
