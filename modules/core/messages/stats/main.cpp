#include <iostream>
#include <string>

#include "StatsMessage.h"

int main(int argc, char** argv){
    try{
	string line("/STATS m irc.efnet.nl");
	StatsMessage* sm = new StatsMessage(line);
	
	cout << sm->translate() << endl;
	delete sm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
