#include "SkaarConfigSection.h"

#include <iostream>

SkaarConfigSection::SkaarConfigSection(string name){
    cout << "DEBUG: SkaarConfigSection(" << name << ")" << endl;
    _name = name;
}

SkaarConfigSection::~SkaarConfigSection(){}

string SkaarConfigSection::name(){
    return _name;
}

string SkaarConfigSection::get(string setting){
    map<string, string>::iterator it = _entries.find(setting);
    
    if(it == _entries.end()){
	return "";
    }
    return _entries[setting];
}

void SkaarConfigSection::set(string setting, string value){
    cout << "DEBUG: Entry: " << setting << ", value: " << value << endl;
    _entries[setting] = value;
}

const map<string, string> SkaarConfigSection::all(){
    return _entries;
}
