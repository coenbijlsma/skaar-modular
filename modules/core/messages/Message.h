#ifndef MESSAGE_H
#define MESSAGE_H

#define CRLF "\r\n"

#include <string>
#include <vector>

#include "../../../tools/StringTokenizer.h"
#include "../connection/IRCConnection.h"
#include "../user/User.h"
#include "../main/Channel.h"

using namespace std;

class Message {
protected:
    string 		_command;
    vector<string> 	_params;
    User*		_user;
    Channel*		_channel;
    string		_raw;
    
    void _init(){
	if(_raw.at(0) == '/'){
	    StringTokenizer st(_raw, ' ');
	    
	    // Set the command
	    _command = string(st.next()).substr(1);
	    
	    // Insert the parameters
	    while(st.hasNext()){
		string _tmp(st.next());
		
		/* 
		 * Check if the parameter starts with
		 * a colon, indicating a parameter 
		 * that contains spaces.
		 */
		if(_tmp.at(0) == ':'){
		    _params.push_back(_tmp);
		    
		    while(st.hasNext()){
			_params.push_back(string(st.next()));
		    }
		    break;
		}else{
		    _params.push_back(_tmp);
		}
	    }
	    
	}else{
	    throw "Invalid message: " + _raw;
	}
	
    }
    
public:

    virtual ~Message();
        
    /*
     * Translates the raw string given during 
     * construction to a string that is fully 
     * compliant with RFC 1459.
     */
    virtual string translate() =0;
    
    /*
     * Returns the command of the message
     */
    virtual const string command() =0;
    
    /*
     * Returns the parameters that accompany 
     * this message.
     */
    virtual const vector<string> params() =0;
    
    /*
     * Sets the User that sends this message
     */
     virtual bool setUser(User* user) =0;
    
    /*
     * Sets the channel this message 
     * is to be sent on.
     */
    virtual bool setChannel(Channel* channel) =0;
    
    /*
     * Actually transmits the message.
     */
    virtual bool transmit(IRCConnection* conn) =0;
    
    /*
     * Re-initializes the message with new
     * contents.
     */
    virtual bool reInit(string raw) =0;
};

typedef Message* create_t(string);
typedef void destroy_t(Message*);

#endif
