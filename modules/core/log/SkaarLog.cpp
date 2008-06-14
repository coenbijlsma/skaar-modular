#include "SkaarLog.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sys/stat.h>

/* Constructor */
SkaarLog::SkaarLog(){
    _filename = LOGFILE;
    _filename.append(".");
    _filename.append(_getDateTime(string("%Y%m%d")));    
}

/* Constructor */
SkaarLog::SkaarLog(string basename){
    _filename = basename;
    _filename.append(".");
    _filename.append(_getDateTime(string("%Y%m%d")));
}

/* Destructor */
SkaarLog::~SkaarLog(){
    if(_entries.size() > 0){
	if( ! save() ){
	    cerr << "ERROR: Some entries have not been logged because of an error." << endl;
	}
    }
}

/* Returns a string containing the current time. */
string SkaarLog::_getDateTime(string format = "%Y-%m-%d %H:%M:%S"){
    time_t 	t_time = time(0);
    char	c_time[256];
    
    strftime(c_time, sizeof(c_time), format.c_str(), localtime(&t_time));
    return string(c_time);
}

/* Appends an entry to the log */
void SkaarLog::append(string log, loglevel_t severity, bool add_extras){
    ostringstream _entry;
    
    _entry << _getDateTime() << "\t" << severity << "\t" << log;
    cout << "Adding log entry: " << _entry.str() << endl;
    _entries.push_back(_entry.str());
}

/* Stores the appended entries in the logfile. */
bool SkaarLog::save(){
    ofstream outfile(_filename.c_str(), ios::out | ios::app);
    
    if( ! outfile){
	cerr << "Could not open file." << endl;
	return false;
    }
    
    for(int i = 0; i < _entries.size(); i++){
	outfile << _entries.at(i) << endl;
    }
    
    outfile.close();
    _entries.clear();
    return true;
}

/* Class factory methods */
extern "C" SkaarLog* create_log(string filename){
    return new SkaarLog(filename);
}

extern "C" void destroy_log(SkaarLog* log){
    delete log;
}
