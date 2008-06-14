#include <iostream>
#include <string>

#include "PrivmsgMessage.h"

int main(int argc, char** argv){
    try{
	string line("/say What's up?");
	PrivmsgMessage* pm = new PrivmsgMessage(line);
	pm->addReceiver("#skaar");
	cout << pm->translate() << endl;
	delete pm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
