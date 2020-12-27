#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

/**
 * The maximum size of the log message content.
 */
#define MAX_LOG_MSG_LENGTH 256

/**
 * The different log levels we support.
 */
typedef enum log_level_e {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
} log_level_e;

/**
 * Make the different log functions public.
 */
void log_debug(const char *fmt, ...);
void log_warning(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_fatal(const char* fmt, ...);

#endif
