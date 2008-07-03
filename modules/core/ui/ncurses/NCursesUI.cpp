#include <string>
#include <ncurses.h>
#include <limits.h>

#include "VirtualUI.h"
#include "UIException.h"
#include <vector>

using namespace std;

class NCursesUI : public VirtualUI {
private:
    vector<VirtualChatWindow*> _windows;
    VirtualChatWindow* _activeWindow;
    
public:
    NCursesUI(){
	initscr();
    }
    
    VirtualChatWindow* activeWindow(){
	return _activeWindow;
    }
    
    VirtualChatWindow* addNewWindow(){
	return (VirtualChatWindow*)0;
    }
    
    VirtualchatWindow* setActive(int n){
	if(_window.size() < (n -1)){
	    throw UIException("The window you requested doesn't exist.");
	}
	return 
    }
    
    
    void endUI(){
	endwin();
    }
    
};

// CLASS FACTORIES
extern "C" VirtualUI* create_ui(){
    return (VirtualUI*) new NCursesUI();
}

extern "C" void destroy_ui(VirtualUI* ui){
    getch(); // jus for testing purposes to see the real output on the screen
    ( (NCursesUI*)ui)->endUI();
    delete ui;
}
