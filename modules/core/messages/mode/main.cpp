#include <iostream>
#include <string>

#include "ModeMessage.h"

int main(int argc, char** argv){
    try{
	string line("/MODE #testchannel +imz");
	ModeMessage* mm = new ModeMessage(line);
	
	cout << mm->translate() << endl;
	delete mm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
