#include <iostream>

#include "User.h"

int main(int argc, char** argv){
    User* u = new User("Coen Bijlsma", "coenie", "passwd");
    cout << "Password for user " << u->getUsername() << ": " << u->getPassword() << endl;
    delete u;
}

