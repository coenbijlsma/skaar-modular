#include <iostream>
#include <string>

#include "ListMessage.h"

int main(int argc, char** argv){
    try{
	string line("/LIST #test irc.efnet.nl");
	ListMessage* lm = new ListMessage(line);
	
	cout << lm->translate() << endl;
	delete lm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
