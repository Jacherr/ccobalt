#ifndef LOG_H
#define LOG_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __LOG_ENV "LOG_LEVEL"
#define __LOG_DEFAULT WARN

#define __LOG_WITH_PRECEDING_LEVEL(__precede, __fmt, ...) char *__path = executable_path(); \
    fprintf(stderr, "%s: %s: ", __path, __precede); \
    fprintf(stderr, __fmt __VA_OPT__(,) __VA_ARGS__); \
    fprintf(stderr, "\n");

enum __log_level
{
    #define __ERROR_STR "error"
    ERROR, /* error is always enabled because this is often reporting of fatal problems */
    #define __WARN_STR "warn"
    WARN,
    #define __INFO_STR "info"
    INFO,
    #define __DEBUG_STR "debug"
    DEBUG,
};

static char __executable_path[PATH_MAX] = { 0 };

static char *executable_path()
{
    #define PATHSYM "/proc/self/exe"

    if(__executable_path[0] != 0)
    {
        return __executable_path;
    }

    readlink(PATHSYM, __executable_path, PATH_MAX);
    if(__executable_path[0] == 0)
    {
        return "ccobalt";
    }

    return __executable_path;
}

static enum __log_level get_log_level()
{
    #define __LEVEL_IF_EQ(env, level) if(strcmp(env, logenv) == 0) \
    { \
        return level; \
    }

    static char gotenv = 0;
    static char *logenv; 
    
    if(!gotenv)
    {
        gotenv = 1;
        logenv = getenv(__LOG_ENV);
    }

    if(logenv == NULL)
    {
        return __LOG_DEFAULT; 
    }

    __LEVEL_IF_EQ(__ERROR_STR, ERROR);
    __LEVEL_IF_EQ(__WARN_STR, WARN);
    __LEVEL_IF_EQ(__INFO_STR, INFO);
    __LEVEL_IF_EQ(__DEBUG_STR, DEBUG);

    return __LOG_DEFAULT;
}

static char should_log(enum __log_level level)
{
    enum __log_level current = get_log_level();
    return current >= level;
}

/* errors always log */
#define ERRORF(__fmt, ...) LOG_WITH_PRECEDING_LEVEL(__ERROR_STR , __fmt, __VA_ARGS__)

#define WARNF(__fmt, ...) if(should_log(WARN)) \
{ \
    __LOG_WITH_PRECEDING_LEVEL(__WARN_STR, __fmt, __VA_ARGS__) \
}

#define INFOF(__fmt, ...) if(should_log(INFO)) \
{ \
    __LOG_WITH_PRECEDING_LEVEL(__INFO_STR, __fmt, __VA_ARGS__) \
}

#define DEBUGF(__fmt, ...) if(should_log(DEBUG)) \
{ \
    __LOG_WITH_PRECEDING_LEVEL(__DEBUG_STR, __fmt, __VA_ARGS__) \
}

#endif /* #ifndef LOG_H */