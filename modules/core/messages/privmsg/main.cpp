#include <iostream>
#include <string>

#include "PrivmsgMessage.h"

int main(int argc, char** argv){
    try{
	string line("/PRIVMSG #test What's up?");
	PrivmsgMessage* pm = new PrivmsgMessage(line);
	cout << pm->translate() << endl;
	delete pm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
