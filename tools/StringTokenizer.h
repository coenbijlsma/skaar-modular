#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class StringTokenizer {
    char* 	_sequence;
    char 	_delimeter;
    int 	_currentLoc;
    char* 	_currentToken;
    char* 	_nextToken;
    
public:
    Stringtokenizer(char* seq, char delim);
    ~Stringtokenizer();
    
    bool hasNext();
    int count();
    char* next();
};

#endif
