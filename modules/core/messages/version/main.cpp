#include <iostream>
#include <string>

#include "VersionMessage.h"

int main(int argc, char** argv){
    try{
	string line("/VERSION irc.efnet.nl");
	VersionMessage* vm = new VersionMessage(line);
	
	cout << vm->translate() << endl;
	delete vm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
