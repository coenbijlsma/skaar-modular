#ifndef VIRTUALUI_H
#define VIRTUALUI_H

#define IRC_MAX_LINE 512

#include <string>

using namespace std;

class VirtualUI {

public:

    /*
     * Prints the provided chars to the UI 
     */
    virtual bool 	print(string chars,  bool error) =0;
    
    /*
     * Appends the newline character to the line, and prints the line.
     */
    virtual bool	printline(string ln, bool error) =0;
    
    /*
     * Reads a line from the UIs' input
     */
    virtual string 	readline() =0;    
};

typedef VirtualUI* create_ui_t();
typedef void destroy_ui_t(VirtualUI*);

#endif
