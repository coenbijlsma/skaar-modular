#ifndef NCURSESCHATWINDOW_H
#define NCURSESCHATWINDOW_H

#define MAX_INSERT_HISTORY 512

#include "VirtualChatWindow.h"
#include <string>
#include <vector>

using namespace std;

class NCursesChatWindow : public VirtualChatWindow {
private:
    vector<string> _inputs;
    WINDOW* _window;
    
public:
    NCursesChatWindow();
    NCursesChatWindow(WINDOW* window);
    
    virtual ~NcursesChatWindow();
    
    /*
     * Prints the line to the chatwindow,
     * appending a newline character.
     */
    bool printline(string);
    
    /*
     * Prints the line to the chatwindow,
     * without appending a newline character.
     */
    bool print(string);
    
    /*
     * Returns the line inserted
     * n inserts ago, with a maximum
     * of MAX_INSERT_HISTORY
     */
    string gethistory(int);
    
    /*
     * Returns the ncurses window
     * that is contained in 
     * this chatwindow.
     */
    WINDOW* ncWINDOW();
    
};

typedef NCursesChatWindow* create_chatwindow_t();
typedef void destroy_chatwindow_t(NCursesChatWindow*);

#endif
