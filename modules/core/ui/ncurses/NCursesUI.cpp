#include <string>
#include <ncurses.h>
#include <limits.h>

#include "VirtualUI.h"
#include "NCursesChatWindow.h"
#include "UIException.h"
#include <vector>

using namespace std;

class NCursesUI : public VirtualUI {
private:
    vector<NCursesChatWindow*> _windows;
    NCursesChatWindow* _activeWindow;
    NCursesChatWindow* _main;
    
public:
    NCursesUI(){
	_main = new NCursesChatWindow(initscr());
	_windows.push_back(_main);
	setActive(0);
    }
    
    ~NCursesUI(){
	_windows.clear();
	endwin();
    }
    
    VirtualChatWindow* activeWindow(){
	return (VirtualChatWindow*)_activeWindow;
    }
    
    VirtualChatWindow* addNewWindow(){
	NCursesChatWindow* _window = new NCursesChatWindow();
	_windows.push_back(_window);
	return (VirtualChatWindow*)_window;
    }
    
    VirtualChatWindow* setActive(int n){
	if(_windows.size() < (n -1) || n < 0){
	    throw UIException("The window you requested doesn't exist.");
	}
	_activeWindow = _windows.at(n);
	return (VirtualChatWindow*)_activeWindow;
    }
    
    bool destroyWindow(int n){
	if(_windows.size() < (n -1) || n < 0){
	    throw UIException("The window you requested doesn't exist.");
	}
	_windows.erase(_windows.begin() + n);
	return true;
    }
    
    bool destroyWindow(VirtualChatWindow* window){
	for(int i = 0; i < _windows.size(); i++){
	    if(_windows.at(i) == window){
		return destroyWindow(i);
	    }	    
	}
	return false;
    }
    
    char* readline(){
	char* tmp = new char[513];
	wgetnstr(_activeWindow->ncWINDOW(), tmp, 513);
	return tmp;
    }
};

// CLASS FACTORIES
extern "C" VirtualUI* create_ui(){
    return (VirtualUI*) new NCursesUI();
}

extern "C" void destroy_ui(VirtualUI* ui){
    getch();
    delete ui;
}
