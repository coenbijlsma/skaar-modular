#include "GenericMessage.h"

#include <iostream>
#include <string>

int main(int argc, char** argv){
    GenericMessage* gm = new GenericMessage(":coen_!~coen@cp393720-a.roemd1.lb.home.nl QUIT :leaving\n\r");
    cout << "Command == " << gm->command() << endl;
    delete gm;
}
