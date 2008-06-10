#include "QuitMessage.h"

#include <string>
#include <iostream>
//#include <dlfcn.h>

using namespace std;


int main(int argc, char** argv){

/*
    void* message = dlopen("/usr/local/lib/libquitmessage.so", RTLD_LAZY);
    
    cout << "Library loaded" << endl;
    
    if(!message){
	cerr << "Cannot load library: " << dlerror() << endl;
	return 1;
    }
    
    dlerror();
    
    create_qmessage_t* create_msg = (create_qmessage_t*) dlsym(message, "create_qmessage");
    const char* dlsym_error = dlerror();
    
    if(dlsym_error){
	cerr << "Cannot load symbol create: " << dlsym_error << endl;
	return 1;
    }
    
    destroy_qmessage_t* destroy_msg = (destroy_qmessage_t*) dlsym(message, "destroy_qmessage");
    dlsym_error = dlerror();
    if(dlsym_error){
	cerr << "Cannot load symbol destroy: " << dlsym_error << endl;
	return 1;
    }
    
    cout << "All loaded" << endl;
*/    
    try{
	QuitMessage* msg = new QuitMessage("/quit Ik ben weg");
	cout << msg->translate() << endl;
//	destroy_msg(msg);
    }catch(string msg){
	cerr << "Error: " << msg << endl;
//	dlclose(message);
	return 1;
    }
    
//    dlclose(message);
}

