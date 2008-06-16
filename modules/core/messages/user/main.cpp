#include <iostream>
#include <string>

#include "UserMessage.h"

int main(int argc, char** argv){
    try{
	string line("/USER coen 0 0 Coen Bijlsma");
	UserMessage* nm = new UserMessage(line);
	
	cout << nm->translate() << endl;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
