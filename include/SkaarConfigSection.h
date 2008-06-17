#ifndef SKAARCONFIGSECTION_H
#define SKAARCONFIGSECTION_H

#include <map>
#include <string>

using namespace std;

class SkaarConfigSection {

private:
    string			_name;
    map<string, string>		_entries;
    
public:
    SkaarConfigSection(string name);
    ~SkaarConfigSection();
    
    string			name();
    string 			get(string setting);
    void			set(string setting, string value);
    const map<string, string> 	all();
    
};

#endif
