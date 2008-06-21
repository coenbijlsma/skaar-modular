#include <iostream>
#include <string>

#include "OperMessage.h"

int main(int argc, char** argv){
    try{
	string line("/OPER foo bar");
	UserMessage* nm = new UserMessage(line);
	
	cout << nm->translate() << endl;
	delete nm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
