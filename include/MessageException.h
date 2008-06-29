#ifndef MESSAGEEXCEPTION_H
#define MESSAGEEXCEPTION_H

#include <exception>

using namespace std;

class MessageException : public exception {
private:
    const char* _what;
    
public:
    MessageException(const char* what) throw();
    virtual ~MessageException() throw();
    
    virtual const char* what() const throw();
};

#endif
