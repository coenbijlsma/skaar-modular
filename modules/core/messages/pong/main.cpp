#include <iostream>
#include <string>

#include "PongMessage.h"

int main(int argc, char** argv){
    try{
	string line("/PONG csd.bu.edu tolsun.oulu.fi");
	PongMessage* pm = new PongMessage(line);
	
	cout << pm->translate() << endl;
	delete pm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
