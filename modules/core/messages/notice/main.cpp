#include <iostream>
#include <string>

#include "NoticeMessage.h"

int main(int argc, char** argv){
    try{
	string line("/NOTICE coen What's up?");
	NoticeMessage* nm = new NoticeMessage(line);
	
	cout << nm->translate() << endl;
	delete nm;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
