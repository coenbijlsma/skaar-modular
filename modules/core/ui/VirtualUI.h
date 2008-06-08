#ifndef VIRTUALUI_H
#define VIRTUALUI_H

class VirtualUI {

public:
    virtual bool 	println(char* line,  bool error) =0;
    virtual char* 	readln() =0;    
};

typedef VirtualUI* create_t();
typedef void destroy_t(VirtualUI*);

#endif
