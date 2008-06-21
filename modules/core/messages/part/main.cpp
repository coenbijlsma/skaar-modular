#include <iostream>
#include <string>

#include "PartMessage.h"

int main(int argc, char** argv){
    try{
	string line("/PART #coenschannel,#testchannel");
	PartMessage* pm = new PartMessage(line);
	
	cout << pm->translate() << endl;
	delete pm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
