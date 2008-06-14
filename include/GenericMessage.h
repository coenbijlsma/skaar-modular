#ifndef GENERICMESSAGE_H
#define GENERICMESSAGE_H

#ifndef CRLF
#define CRLF "\n\r"
#endif

#include <string>
#include <vector>

using namespace std;

class GenericMessage {
private:
    string 			_raw;
    string			_command;
    string			_prefix;
    vector<string> 		_params;

    void 			_init();

public:
    
    GenericMessage(string raw);
    ~GenericMessage();
    
    string 			translate();
    const string 		prefix();
    const string 		command();
    const vector<string> 	params();
        
};

typedef GenericMessage* create_genericmesage_t(string);
typedef void destroy_genericmessage_t(GenericMessage*);

#endif
