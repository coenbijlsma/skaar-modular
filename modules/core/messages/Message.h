#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "StringTokenizer.h"
#include "IRCConnection.h"
#include "User.h"
#include "Channel.h"

using namespace std;

class Message {

public:

    /*
     * Translates the raw message
     * to a RFC 1459 compliant string.
     */
    string translate();
};

typedef Message* create_message_t(string raw);
typedef void destroy_message_t(Message*);

#endif
