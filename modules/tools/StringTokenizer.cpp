#include "StringTokenizer.h"

StringTokenizer::StringTokenizer(std::string seq, char delim){
    char* ptr;
    if(seq.c_str() == '\0'){
	fprintf(stderr, "The sequence to be checked cannot be NULL\n");
	return;
    }else{
	char* _tmp = (char*)malloc(seq.size() +1);
	memset(_tmp, 0, seq.size() +1);
	
	strcpy(_tmp, seq.c_str());
	_sequence = _tmp;
    }
    
    if(delim == 0){
	_delimeter = ' ';
    }else{
	_delimeter = delim;
    }

    _currentLoc = 0;
    _currentToken = 0;
    if( (ptr = strchr(_sequence, delim)) == 0){
	_nextToken = (char*)malloc(strlen(_sequence) +1);
	memset(_nextToken, 0, strlen(_sequence) +1);
	strcpy(_nextToken, _sequence);
    }else{
	_nextToken = (char*)malloc(ptr - _sequence + 1);
	memset(_nextToken, 0, ptr - _sequence + 1);
	strncpy(_nextToken, _sequence, ptr - _sequence);
	_currentLoc = ptr - _sequence;
    }
    
}

StringTokenizer::~StringTokenizer(){
    free(_currentToken);
    free(_nextToken);
}

bool StringTokenizer::hasNext(){
    if(_nextToken == 0){
	return false;
    }
    return true;
}

int StringTokenizer::count(){
    int tok = 1;
    
    for(int i = 0; i <= strlen(_sequence); i++){
	if(_sequence[i] == _delimeter){
	    tok++;
	}
    }
    return tok;
}

char* StringTokenizer::next(){
    char* ptr;
    char* ptr2;
    char* retval;
    
    if(_nextToken == 0){
	return 0;
    }
    
    if(_currentToken != 0){
	free(_currentToken);
    }
    
    // copy _nextToken into _currentToken
    _currentToken = (char*)malloc(strlen(_nextToken) +1);
    memset(_currentToken, 0, strlen(_nextToken) +1);
    strcpy(_currentToken, _nextToken);
    
    // shift until next _delimeter
    for(ptr = _sequence + _currentLoc; ptr[0] != '\0' && ptr[0] != _delimeter; ptr++){}
    
    //(re)fill _nextToken
    free(_nextToken);
    if(ptr[0] == '\0'){
	_nextToken = 0;
    }else{
	ptr++;
	ptr2 = strchr(ptr, _delimeter);
	
	if(ptr2 == 0){
	    // if this is the last token
	    _nextToken = (char*)malloc(strlen(ptr) +1);
	    memset(_nextToken, 0, strlen(ptr) +1);
	    strcpy(_nextToken, ptr);
	}else{
	    _nextToken = (char*)malloc(ptr2 - ptr + 1);
	    memset(_nextToken, 0, ptr2 - ptr + 1);
	    strncpy(_nextToken, ptr, ptr2 - ptr);
	}
	_currentLoc += strlen(_nextToken) + 1;
    }
    
    retval = (char*)malloc(strlen(_currentToken) +1);
    memset(retval, 0, strlen(_currentToken) +1);
    strcpy(retval, _currentToken);
    return retval;
}
