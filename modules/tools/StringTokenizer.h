#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

class StringTokenizer {
    char* 	_sequence;
    char 	_delimeter;
    int 	_currentLoc;
    char* 	_currentToken;
    char* 	_nextToken;
    
public:
    StringTokenizer(string seq, char delim);
    ~StringTokenizer();
    
    bool hasNext();
    int count();
    char* next();
};

#endif
