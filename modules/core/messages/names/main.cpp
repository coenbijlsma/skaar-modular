#include <iostream>
#include <string>

#include "NamesMessage.h"

int main(int argc, char** argv){
    try{
	string line("/NAMES #test,#test1");
	NamesMessage* nm = new NamesMessage(line);
	
	cout << nm->translate() << endl;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
