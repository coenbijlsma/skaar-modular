#include <string>
#include <iostream>

#include "PassMessage.h"

using namespace std;

int main(int argc, char** argv){
    
    try{
	string line("/PASS test");
	PassMessage* msg = new PassMessage(line);
	
	cout << msg->translate() << endl;
    }catch(string msg){
	cerr << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}

