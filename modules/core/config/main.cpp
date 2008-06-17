#include "SkaarConfig.h"
#include "SkaarConfigSection.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
    SkaarConfig* config = new SkaarConfig(string("skaar.conf"));
    SkaarConfigSection* scs = config->getSection("channels");
    
    cout << "Channel(s) for localhost: " << scs->get("localhost") << endl;

    delete config;
}
