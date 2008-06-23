#include <iostream>
#include <string>

#include "WhowasMessage.h"

int main(int argc, char** argv){
    try{
	string line("/WHOWAS Trillian 1 *.edu") ;
	WhowasMessage* wm = new WhowasMessage(line);
	
	cout << wm->translate() << endl;
	delete wm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
