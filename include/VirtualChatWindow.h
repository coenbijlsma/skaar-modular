#ifndef VIRTUALCHATWINDOW_H
#define VIRTUALCHATWINDOW_H

using namespace std;

class VirtualChatWindow {

public:

    /* 
     * Prints the line to the chatwindow
     */
    virtual bool printline(string ln) =0;
};

typedef VirtualChatWindow* create_chatwindow_t();
typedef void destroy_chatwindow_t(VirtualChatWindow*);

#endif
