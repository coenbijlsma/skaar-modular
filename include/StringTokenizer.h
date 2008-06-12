#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

class StringTokenizer {
private:
    char* 	_sequence;
    char 	_delimeter;
    int 	_currentLoc;
    char* 	_currentToken;
    char* 	_nextToken;
    
public:
    StringTokenizer(string seq, char delim);
    virtual ~StringTokenizer();
    
    /*
     * Returns true if the string still
     * contains more tokens.
     */
    bool 	hasNext();
    
    /*
     * Returns the amount of tokens.
     */
    int 	count();
    
    /*
     * Returns the next token,
     * and prepares the token after
     * that for takeoff (if any).
     * If there are no more tokens,
     * this function returns NUL.
     */
    char* 	next();
};

typedef StringTokenizer* create_tokenizer_t(string seq, char delim);
typedef void destroy_tokenizer_t(StringTokenizer*);

#endif
