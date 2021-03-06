#include "Skaar.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
    cout << "Starting..." << endl;
    
    Skaar* skaar = new Skaar();
    
    try{
	skaar->init();
	//cout << "INIT" << endl;
	skaar->startWork();
	cout << "startWork()" << endl;
    }catch(string msg){
	cerr << msg << endl;
	delete skaar;
	return 1;
    }
    cout << "That was skaar..." << endl;
    delete skaar;
    return 0;
}
