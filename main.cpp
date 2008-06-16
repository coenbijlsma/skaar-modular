#include "Skaar.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
    Skaar* skaar = new Skaar();
    
    try{
	skaar->init();
	skaar->startWork();
    }catch(string msg){
	cerr << msg << endl;
	return 1;
    }
    return 0;
}
