#include <iostream>
#include <string>

#include "InviteMessage.h"

int main(int argc, char** argv){
    try{
	string line("/INVITE foo #bar");
	InviteMessage* im = new InviteMessage(line);
	
	cout << im->translate() << endl;
	delete im;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
