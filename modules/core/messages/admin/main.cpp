#include <iostream>
#include <string>

#include "AdminMessage.h"

int main(int argc, char** argv){
    try{
	string line("/ADMIN irc.efnet.nl");
	AdminMessage* am = new AdminMessage(line);
	
	cout << am->translate() << endl;
	delete am;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
