#ifndef SKAARLOG_H
#define SKAARLOG_H

#include <string>
#include <vector>

#define MAXLOGFILES 20
#define LOGFILE "skaar.log"

using namespace std;

class SkaarLog {
private:
    string		_filename;
    vector<string>	_entries;
    
    string		_getDateTime(string);

public:
    enum loglevel_t {LOG_USER = 0, LOG_INFO, LOG_NOTICE, LOG_WARNING, LOG_ERROR, LOG_FAILURE};
    
    /* 
     * Constructor.
     * Constructs a new log with filename
     * LOGFILE. The current date in the form
     * of YYYYMMDD is appended to the filename.
     */
    SkaarLog();
    
    /*
     * Constructor.
     * Constructs a new log with the
     * specified filename. The current date
     * is appended in the form of YYYYMMDD.
     */
    SkaarLog(string);
    
    /*
     * Destructor. 
     * If the vector _entries is not empty,
     * the entries are stored in the file 
     * if possible.
     */
    ~SkaarLog();
    
    /*
     * Appends the specified entry to the log.
     * If add_extras is set to true, entries are 
     * logged in the following format:
     * <time> <log_level> <log_entry> 
     * 
     * If add_extras is false, only the log message
     * is appended to the logfile.
     */
    void append(string log, loglevel_t severity = LOG_USER, bool add_extras = false);
    
    /*
     * Stores the inserted entries in the file.
     * If no filename is given in the constructor,
     * the filename will be skaar.log. If that fil
     * already exists, the log will be skaar.log.1, 
     * and so on.
     *
     * After the entries have been saved, the entries will
     * be deleted from the vector, and new entries can
     * be added until the next save() stores them in the logfile.
     */
    bool save();
};

typedef SkaarLog* create_log_t();
typedef void destroy_log_t(SkaarLog*);

#endif
