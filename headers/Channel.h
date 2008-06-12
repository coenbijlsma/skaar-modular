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
    
    const string getName();
};

typedef Channel* create_channel_t(string);
typedef void destroy_channel_t(Channel*);

#endif
