#include <iostream>
#include <string>

#include "UserMessage.h"

int main(int argc, char** argv){
    try{
	string line("/USER coen 0 0 Coen Bijlsma");
	UserMessage* um = new UserMessage(line);
	
	cout << um->translate() << endl;
	delete um;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
