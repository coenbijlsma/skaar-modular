#include <iostream>
#include <string>

#include "KickMessage.h"

int main(int argc, char** argv){
    try{
	string line("/KICK #test foo You are a bitch");
	KickMessage* km = new KickMessage(line);
	
	cout << km->translate() << endl;
	delete km;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
