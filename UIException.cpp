#include "UIException.h"

UIException::UIException(const char* what) throw(){
    _what = what;
}

UIException::~UIException() throw(){}

const char* UIException::what() const throw(){
    return _what;
}
