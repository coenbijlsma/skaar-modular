#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>

using namespace std;

class Channel {
private:
    string _name;
    
public:
    Channel(string name);
    ~Channel();
    
    string getName();
};


#endif
