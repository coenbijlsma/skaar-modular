#ifndef SKAARLOG_H
#define SKAARLOG_H

#include <string>
#include <vector>

#define MAXLOGS 20
#define LOGFILE "skaar.log"

using namespace std;

class SkaarLog {
private:
    vector<string>	_entries;

public:
    static enum loglevel_t {LOG_USER = 0, LOG_INFO = 1, LOG_NOTICE = 2, LOG_WARNING = 3, LOG_ERROR = 4, LOG_FAILURE = 5};
    
    SkaarLog();
    SkaarLog(string filename);
    ~SkaarLog();
    
    /*
     * Appends the specified entry to the log.
     * Entries are logged in the following format:
     * <time> <log_level> <log_entry> 
     */
    bool append(string log, loglevel_t severity = 0);
    
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
