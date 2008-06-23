#include <iostream>
#include <string>

#include "InfoMessage.h"

int main(int argc, char** argv){
    try{
	string line("/INFO irc.efnet.nl");
	InfoMessage* im = new InfoMessage(line);
	
	cout << im->translate() << endl;
	delete im;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
