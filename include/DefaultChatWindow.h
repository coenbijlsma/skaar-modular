#ifndef DEFAULTCHATWINDOW_H
#define DEFAULTCHATWINDOW_H

#include "VirtualChatWindow.h"
#include <string>

using namespace std;

class DefaultChatWindow : public VirtualChatWindow {

public:
    DefaultChatWindow();
    virtual ~DefaultChatWindow();
    
    bool printline(string);
    bool print(string);
};

typedef DefaultChatWindow* create_chatwindow_t();
typedef void destroy_chatwindow_t(DefaultChatWindow*);

#endif
