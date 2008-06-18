#include <string>
#include <ncurses.h>
#include <limits.h>

#include "VirtualUI.h"

using namespace std;

class NCursesUI : public VirtualUI {

public:
    NCursesUI(){
	initscr();
    }
    
    bool print(string line, bool error){
	if(printw(line.c_str()) != OK){
	    refresh();
	    return false;
	}
	refresh();
	return true;
    }
    
    bool printline(string line, bool error){
	line.append("\n");
	return print(line, error);
    }
    
    string readline(){
	char str[LINE_MAX];
	if(getstr(str) != OK){
	    return NULL;
	}else{
	    return string(str);
	}
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
    getch();
    ( (NCursesUI*)ui)->endUI();
    delete ui;
}
