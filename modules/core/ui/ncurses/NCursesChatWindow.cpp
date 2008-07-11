#include "NCursesChatWindow.h"
#include "UIException.h"
#include <ncurses.h>

NCursesChatWindow::NCursesChatWindow(){
    // XXX Should I use stdscr??
    _window = dupwin(stdscr);
    if(_window = NULL){
	throw UIException("Could not create subwindow.");
    }
}

NCursesChatWindow::NCursesChatWindow(WINDOW* window){
    _window = window;
}

NCursesChatWindow::~NCursesChatWindow(){
    if( delwin(_window) == ERR ){
	throw UIException("Could not delete window.");
    }
}

bool NCursesChatWindow::printline(string ln){
    if( ! ln.empty() ){
        ln.append("\n");
	return this->print(ln);
    }
    return false;
}

bool NCursesChatWindow::print(string ln){
    if( ! ln.empty() ){
	/* Check if printing the line succeeded */
        if( wprintw(_window, ln) == ERR ){
	    return false;
	}
	
	/* 
	 * Delete the line a the beginning if the maxmimum
	 * has been reached.
	 */
	if(_inserts.size >= MAX_INSERT_HISTORY){
	    _inputs.erase(_inputs.begin());
	}
	
	/* Save the inserted line */
	_inputs.push_back(ln);
	return true;
    }
    return false;
}

string NCursesWindow::gethistory(int n){
    if( n > MAX_INSERT_HISTORY || n > (_inserts.size() -1) ){
	throw UIException("");
    }
    return _lines.at( _inserts.size() - n);
}

WINDOW* NCursesChatWindow::ncWINDOW(){
    return _window;
}

/* Class Factories */
extern "C" NCursesChatWindow* create_chatwindow(){
    return new NCursesChatWindow;
}

extern "C" void destroy_chatwindow(NCursesChatWindow* window){
    delete window;
}
