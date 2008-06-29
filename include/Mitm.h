#ifndef MITM_H
#define MITM_H

#include <string>
#include "IRCMessage.h"

class Mitm {
private:
    Skaar* _skaar;
    string _raw;
    IRCMessage* _translation;
    
public:
    Mitm(Skaar* skaar, string raw);
    ~Mitm();
    
    IRCMessage* translate();
};

#endif

