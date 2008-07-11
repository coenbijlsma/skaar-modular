#ifndef VIRTUALUI_H
#define VIRTUALUI_H

#define IRC_MAX_LINE 512

#include <string>
#include "VirtualChatWindow.h"

// XXX LINK THE VirtualChatWindow in the library
// XXX WRITE CODE IN THE .cpp FILE
using namespace std;

class VirtualUI {

public:
    
    virtual ~VirtualUI();
    
    virtual VirtualChatWindow* activeWindow() =0;
    
    virtual VirtualChatWindow* addNewWindow() =0;
    
    virtual VirtualChatWindow* setActive(int) =0;
    
    virtual bool destroyWindow(int) =0;
    
    virtual bool destroyWindow(VirtualCharWindow*) =0;

    virtual char* readline() =0;    
};

typedef VirtualUI* create_ui_t();
typedef void destroy_ui_t(VirtualUI*);

#endif
