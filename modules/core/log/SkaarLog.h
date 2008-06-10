#ifndef SKAARLOG_H
#define SKAARLOG_H

#include <string>

using namespace std;

class SkaarLog {
};

typedef SkaarLog* create_log_t();
typedef void destroy_log_t(SkaarLog*);

#endif
