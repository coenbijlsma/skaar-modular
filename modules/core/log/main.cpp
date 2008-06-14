#include "SkaarLog.h"

int main(int argc, char** argv){
    SkaarLog* log = new SkaarLog("test.log");
    enum SkaarLog::loglevel_t level;
    level = SkaarLog::LOG_USER;
    
    log->append("TEST LOG ENTRY", level);
    if(log->save()){
	delete log;
	return true;
    }else{
	delete log;
	return false;
    }
}
