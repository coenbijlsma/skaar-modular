#include <string>
#include <ncurses.h>
#include <limits.h>

#include "../VirtualUI.h"

using namespace std;

class NCursesUI : public VirtualUI {

public:
    NCursesUI(){
	initscr();
    }
    
    ~NCursesUI(){
	endwin();
    }
    
    bool printline(string line, bool error){
	if(printw(line.c_str()) != OK){
	    return false;
	}
	refresh();
	return true;
    }
    
    string readline(){
	char str[LINE_MAX];
	if(getstr(str) != OK){
	    return NULL;
	}else{
	    return string(str);
	}
    }
    
};

// CLASS FACTORIES
extern "C" VirtualUI* create(){
    return (VirtualUI*) new NCursesUI();
}

extern "C" void destroy(VirtualUI* ui){
    delete ui;
}
