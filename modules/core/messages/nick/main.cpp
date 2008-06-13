#include <iostream>
#include <string>

#include "NickMessage.h"

int main(int argc, char** argv){
    try{
	string line("/quit coenie 15");
	NickMessage* nm = new NickMessage(line);
	
	cout << nm->translate() << endl;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
