#include <iostream>
#include <string>

#include "JoinMessage.h"

int main(int argc, char** argv){
    try{
	string line("/join #coenschannel,#testchannel passwd");
	JoinMessage* nm = new JoinMessage(line);
	
	cout << nm->translate() << endl;
    }catch(string msg){
	cout << "Error: " << msg << endl;
	return 1;
    }
    return 0;
}
