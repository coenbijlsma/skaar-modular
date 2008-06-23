#include <iostream>
#include <string>

#include "WhoisMessage.h"

int main(int argc, char** argv){
    try{
	string line("/WHOIS foo");
	WhoisMessage* wm = new WhoisMessage(line);
	
	cout << wm->translate() << endl;
	delete wm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
