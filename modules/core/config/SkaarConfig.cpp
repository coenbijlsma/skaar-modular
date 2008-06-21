#include "SkaarConfig.h"
#include "StringTokenizer.h"

/* Constructor */
SkaarConfig::SkaarConfig(string filename){
    _filename = filename;
    
    ifstream _ifstream(_filename.c_str(), ios::in);
    
    if( ! _ifstream.is_open()){
	cerr << "File not found, trying default config." << endl;
	_filename = string(DEFAULT_CONFIGFILE);
	_ifstream.open(_filename.c_str(), ios::in);
	
	if( ! _ifstream.is_open()){
	    cerr << "Default config not found, creating one." << endl;
	    _writeDefaultConfig();
	    _ifstream.open(_filename.c_str(), ios::in);
	    
	    if( ! _ifstream.is_open()){
		throw "Could not create default config file, exiting.";
	    }
	}
    }else{
	//cout << "DEBUG: File " << filename << " opened" << endl;
    }
    
    _ifstream.close();
    
    _init();
    _filename = filename;
}

/* Destructor */
SkaarConfig::~SkaarConfig(){
    writeConfig();
}

/* Reads the config file */
void SkaarConfig::_init(){
    //cout << "DEBUG: SkaarConfig::_init()" << endl;
    
    ifstream _ifstream(_filename.c_str(), ios::in);
    
    if( ! _ifstream.is_open()){
	_ifstream.close();
	throw string("Could not open file ") + _filename;
    }else{
	//cout << "DEBUG: File " << _filename << " opened for reading." << endl;
    }
    
    string		_line;
    SkaarConfigSection*	_section;
    bool		_inSection = false;
    
    while(getline(_ifstream, _line)){
	//cout << "DEBUG: read line '" << _line << "'." << endl;
	
	if( (! _line.empty()) && _line.at(0) != '#'){
	    //cout << "DEBUG: Found useable line: '" << _line << "'." << endl;
	    
	    if( ! _inSection){
		_section = new SkaarConfigSection(_line);
		_inSection = true;
	    }else{
		if(_line.at(0) != '{' && _line.at(0) != '}'){
		    StringTokenizer st(_line, ' ');
		    
		    /* Only read the entry if the line has 2 tokens */
		    if(st.count() == 2){
			string _setting(st.next());
			string _value(st.next());
			_section->set(_setting, _value); 
		    }else if(st.count() > 2){
			string _setting(st.next());
			string _value(st.next());
			
			while(st.hasNext()){
			    _value.append(" ");
			    _value.append(st.next());
			}
			_section->set(_setting, _value);
		    }
		}else{
		    if(_line.at(0) == '}'){
			_sections[_section->name()] = _section;
			_inSection = false;
		    }
		} // _line.at(0) != '{' && _line.at(0) != '}'
		
	    } // ! _inSection
	    
	} // ! _line.empty() && ! _line.at(0) = '#'
	
    } // while(getline(_fstream, _line))
    
    _ifstream.close();
    
    //cout << "DEBUG: file closed" << endl;
}

/* Writes a section to _fs */
void SkaarConfig::_writeSection(ofstream* _fs, string name){

    if( ! (*_fs).is_open()){
	throw string("Could not access file ") + _filename;
    }
    
    SkaarConfigSection* _section = _sections[name];
    map<string, string> _entries = _section->all();
    map<string, string>::iterator it;
    
    (*_fs) << endl;
    (*_fs) << name << endl;
    (*_fs) << "{" << endl;
    
    for(it = _entries.begin(); it != _entries.end(); it++){
	(*_fs) << (*it).first << " " << (*it).second << endl;
    }
    
    (*_fs) << "}" << endl;
    (*_fs) << endl;
}

/* Creates a default config file */
void SkaarConfig::_writeDefaultConfig(){
    ofstream _ofstream;
    _ofstream.open(_filename.c_str(), ios::out | ios::app);
    
    if( ! _ofstream.is_open()){
	_ofstream.close();
	return;
    }
    
    _ofstream << "# README" 								<< endl;
    _ofstream << "# This file contains the settings that Skaar uses to run properly." 	<< endl;
    _ofstream 										<< endl;    
    _ofstream << "# Core settings" 							<< endl;
    _ofstream 										<< endl;
    _ofstream << "core" 								<< endl;
    _ofstream << "{" 									<< endl;
    _ofstream << "realname \"Lazy foo\"" 						<< endl;
    _ofstream << "nick myname__"							<< endl;
    _ofstream << "password foo"								<< endl;
    _ofstream << "ui /usr/local/lib/libncursesui.so"					<< endl;
    _ofstream << "defaultui /usr/local/lib/libdefaultui.so"				<< endl;
    _ofstream << "}" 									<< endl;
    _ofstream 										<< endl;        
    _ofstream << "# Servers" 								<< endl;
    _ofstream << "# Below you can specify which servers to" 				<< endl;
    _ofstream << "# connect to when skaar starts. If there" 				<< endl;
    _ofstream << "# are no servers specified, you have to " 				<< endl;
    _ofstream << "# connect manually." 							<< endl;
    _ofstream << "# The format for a server config line" 				<< endl;
    _ofstream << "# is as follows:" 							<< endl;
    _ofstream << "# <hostname|ip> <port>" 						<< endl;
    _ofstream 										<< endl;
    _ofstream << "servers"								<< endl;
    _ofstream << "{" 									<< endl;
    _ofstream << "localhost 6667" 							<< endl;
    _ofstream << "}" 									<< endl;
    _ofstream 										<< endl;
    _ofstream << "# Channels" 								<< endl;
    _ofstream << "# You can also specify which channels" 				<< endl;
    _ofstream << "# to connect to on startup." 						<< endl;
    _ofstream << "# The format for this is as follows," 				<< endl;
    _ofstream << "# but has to be the same as the server" 				<< endl;
    _ofstream << "# mentioned above." 							<< endl;
    _ofstream << "# <server|ip> <channel>" 						<< endl;
    _ofstream 										<< endl;
    _ofstream << "channels" 								<< endl;
    _ofstream << "{" 									<< endl;
    _ofstream << "localhost #mychannel" 						<< endl;
    _ofstream << "}" 									<< endl;
    _ofstream 										<< endl;
    _ofstream << "# Message aliases" 							<< endl;
    _ofstream << "# You can also add your own aliases here." 				<< endl;
    _ofstream << "# The format of a alias line is as follows:" 				<< endl;
    _ofstream << "# <alias> <command>" 							<< endl;
    _ofstream 										<< endl;
    _ofstream << "aliases" 								<< endl;
    _ofstream << "{" 									<< endl;
    _ofstream << "j JOIN" 								<< endl;
    _ofstream << "join JOIN" 								<< endl;
    _ofstream << "nick NICK" 								<< endl;
    _ofstream << "pass PASS" 								<< endl;
    _ofstream << "say PRIVMSG" 								<< endl;
    _ofstream << "query PRIVNSG" 							<< endl;
    _ofstream << "quit QUIT" 								<< endl;
    _ofstream << "exit QUIT" 								<< endl;
    _ofstream << "bye QUIT" 								<< endl;
    _ofstream << "signoff QUIT" 							<< endl;
    _ofstream << "user USER" 								<< endl;
    _ofstream << "}" 									<< endl;
    _ofstream 										<< endl;
    
    _ofstream.close();
}

/* Returns the section that has the provided name */
SkaarConfigSection* SkaarConfig::getSection(string name){
    map<string, SkaarConfigSection*>::iterator it = _sections.find(name);
    
    if(it == _sections.end()){
	return 0;
    }
    
    return _sections[name];
}

/* Returns the value of the provided setting in setting */
string SkaarConfig::getValue(string section, string setting){
    map<string, SkaarConfigSection*>::iterator it = _sections.find(section);
    
    if(it == _sections.end()){
	return "";
    }
    
    SkaarConfigSection* scs = _sections[section];
    return scs->get(setting);
}

/* Sets or overwrites a settings' value */
void SkaarConfig::setSetting(string section, string setting, string value){
    map<string, SkaarConfigSection*>::iterator it = _sections.find(section);
    
    if(it == _sections.end()){
	throw string("Section ") + section + string(" does not exist.");
    }
    
    SkaarConfigSection* scs = _sections[section];
    
    scs->set(setting, value);
}

/* Writes the config to a file */
bool SkaarConfig::writeConfig(){
    //cout << "DEBUG: Writing config." << endl;
    
    ofstream _myofstream(_filename.c_str(), ios::in);
    
    if(_myofstream.is_open()){
	_myofstream.open(_filename.c_str(), ios::in | ios::out | ios::app | ios::trunc);
    }else{
	_myofstream.open(_filename.c_str(), ios::in | ios::out | ios::app);
    }
    
    _myofstream << "# README" << endl;
    _myofstream << "# This file contains the settings that Skaar uses to run properly." << endl;
    _myofstream << endl;
    
    /* The core section */
    try{
	_myofstream << "# Core settings" << endl;
	_writeSection(&_myofstream, string("core"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    /* The servers section */
    try{
	_myofstream << "# Servers" << endl;
	_myofstream << "# Below you can specify which servers to" << endl;
	_myofstream << "# connect to when skaar starts. If there" << endl;
	_myofstream << "# are no servers specified, you have to" << endl;
	_myofstream << "# connect manually." << endl;
	_myofstream << "# The format for a server config line" << endl;
	_myofstream << "# is as follows:" << endl;
	_myofstream << "# <hostname|ip> <port>" << endl;
	_myofstream << endl;
	
	_writeSection(&_myofstream, string("servers"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    /* The channels section */
    try{
	_myofstream << "# Channels" << endl;
	_myofstream << "# You can also specify which channels" << endl;
	_myofstream << "# to join at startup." << endl;
	_myofstream << "# The format for this is as follows," << endl;
	_myofstream << "# but has to be the same as the server" << endl;
	_myofstream << "# mentioned above." << endl;
	_myofstream << "# <server|ip> <channel>" << endl;
	
	_writeSection(&_myofstream, string("channels"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    /* The aliases section */
    try{
	_myofstream << "# Mesage aliases" << endl;
	_myofstream << "# You can also add you own aliases here." << endl;
	_myofstream << "# The format of an alias line is as follows:" << endl;
	_myofstream << "# <alias> <command>" << endl;
	
	_writeSection(&_myofstream, string("aliases"));
    }catch(string msg){
	cerr << msg << endl;
    }
    
    _myofstream.close();
    return true;
}

// CLASS FACTORIES 
extern "C" SkaarConfig* create_config(string filename){
    return new SkaarConfig(filename);
}

extern "C" void destroy_config(SkaarConfig* config){
    delete config;
}

