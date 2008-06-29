#ifndef UIEXCEPTION_H
#define UIEXCEPTION_H

#include <exception>

using namespace std;

class UIException : public exception {
private:
    const char* _what;
    
public:
    UIException(const char* what) throw();
    virtual ~UIException() throw();
    
    virtual const char* what() const throw();
};

#endif
