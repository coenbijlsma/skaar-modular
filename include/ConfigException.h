#ifndef CONFIGEXCEPTION_H
#define CONFIGEXCEPTION_H

#include <exception>

using namespace std;

class ConfigException : public exception {
private:
    const char* _what;
    
public:
    ConfigException(const char* what) throw();
    virtual ~ConfigException() throw();
    
    virtual const char* what() const throw();
};

#endif
