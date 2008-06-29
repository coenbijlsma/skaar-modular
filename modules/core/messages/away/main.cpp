#include <string>
#include <iostream>

#include "AwayMessage.h"

using namespace std;

int main(int argc, char** argv){
    
    try{
	string line("/AWAY Ik ben weg");
	
	AwayMessage* msg = new AwayMessage(line);
	
	cout << msg->translate() << endl;
	delete msg;
    }catch(string msg){
	cerr << "Error: " << msg << endl;
	return 1;
    }
    
}

