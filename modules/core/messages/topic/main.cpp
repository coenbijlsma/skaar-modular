#include <iostream>
#include <string>

#include "TopicMessage.h"

int main(int argc, char** argv){
    try{
	string line("/TOPIC #test New topic");
	TopicMessage* tm = new TopicMessage(line);
	
	cout << tm->translate() << endl;
	delete tm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
