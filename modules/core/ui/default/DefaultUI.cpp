#include <iostream>
#include <string>

#include "../VirtualUI.h"

using namespace std;

class DefaultUI : public VirtualUI {
    
public:
    DefaultUI(){}
    
    ~DefaultUI(){}
    
    bool printline(string ln, bool error){
	if(error){
	    cerr << ln << endl;
	}else{
	    cout << ln << endl;
	}
	return true;
    }
    
    string readline(){
	string s;
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
