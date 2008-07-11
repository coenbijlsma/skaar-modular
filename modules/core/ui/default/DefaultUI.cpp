#include <iostream>
#include <string>

#include "VirtualUI.h"
#include "DefaultChatWindow.h"

using namespace std;

class DefaultUI : public VirtualUI {
private:
    DefaultChatWindow* _chatWindow;
        
public:
    DefaultUI(){
	_chatWindow = new DefaultChatWindow();
    }
    
    virtual ~DefaultUI(){}
    
    VirtualChatWindow* activeWindow(){
	return (VirtualChatWindow*)_chatWindow;
    }
    
    VirtualChatWindow* addNewWindow()[
	return (VirtualChatWindow*)_chatWindow;
    }
    
    VirtualChatWindow* setActive(int active){
	return (VirtualChatWindow*)_chatWindow;
    }
    
    bool destroyWindow(int window){
	return false;
    }
    
    bool destroyWindow(VirtualChatWindow* window){
	return false;	
    }
    
    char* readline(){
	char* s;    
	getline(cin, s);
	return s;
    }
};

// CLASS FACTORIES
extern "C" VirtualUI* create_ui(){
    return (VirtualUI*) new DefaultUI();
}

extern "C" void destroy_ui(VirtualUI* ui){
    delete ui;
}
