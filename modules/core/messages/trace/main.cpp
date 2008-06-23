#include <iostream>
#include <string>

#include "TraceMessage.h"

int main(int argc, char** argv){
    try{
	string line("/TRACE irc.efnet.nl");
	TraceMessage* tm = new TraceMessage(line);
	
	cout << tm->translate() << endl;
	delete tm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
