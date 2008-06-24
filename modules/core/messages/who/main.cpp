#include <iostream>
#include <string>

#include "WhoMessage.h"

int main(int argc, char** argv){
    try{
	string line("/WHO foo* n");
	WhoMessage* wm = new WhoMessage(line);
	
	cout << wm->translate() << endl;
	delete wm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
