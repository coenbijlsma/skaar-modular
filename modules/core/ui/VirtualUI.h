#ifndef VIRTUALUI_H
#define VIRTUALUI_H

#define IRC_MAX_LINE 512

#include <string>

using namespace std;

class VirtualUI {

public:
    virtual bool 	printline(string line,  bool error) =0;
    virtual string 	readline() =0;    
};

typedef VirtualUI* create_t();
typedef void destroy_t(VirtualUI*);

#endif
