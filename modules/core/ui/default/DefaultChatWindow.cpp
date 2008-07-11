#include "DefaultChatWindow.h"

#include <iostream>
#include <string>

DefaultChatWindow::DefaultChatWindow(){}

DefaultChatWindow::~DefaultChatWindow(){}

bool DefaultChatWindow::printline(string ln){
    cout << ln << endl;
}

bool DefaultChatWindow::print(string ln){
    cout << ln;
}

extern "C" DefaultChatWindow* create_chatwindow(){
    return new DefaultChatWindow();
}

extern "C" void destroy_chatwindow(DefaultChatWindow* window){
    delete window;
}
