#include <iostream>
#include <string>

#include "PingMessage.h"

int main(int argc, char** argv){
    try{
	string line("/PING foo");
	PingMessage* pm = new PingMessage(line);
	
	cout << pm->translate() << endl;
	delete pm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
