#ifndef VIRTUALCHATWINDOW_H
#define VIRTUALCHATWINDOW_H

#include <string>

using namespace std;

class VirtualChatWindow {

public:

    /* 
     * Prints the line to the chatwindow,
     * and appends the endl object.
     */
    virtual bool printline(string) =0;
    
    /*
     * Prints the line to the chatwindow,
     * but does not append the endl object.
     */
    virtual bool print(string) =0;
};

#endif
