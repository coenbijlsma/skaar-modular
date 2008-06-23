#include <iostream>
#include <string>

#include "LinksMessage.h"

int main(int argc, char** argv){
    try{
	string line("/LINKS *.nl");
	LinksMessage* lm = new LinksMessage(line);
	
	cout << lm->translate() << endl;
	delete lm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
