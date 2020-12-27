#include "log.h"
#include "utils.h"

/**
 *  The actual function that writes the log to the screen.
 */
void log_message(log_level_e lvl, char *msg) {
    char *lvl_str;
    int ansi_color;
    // decide on tag and color
    switch (lvl)
    {
    case LOG_LEVEL_ERROR:
        // ERR and red foreground
        lvl_str = "ERR";
        ansi_color = 31;
        break;

    case LOG_LEVEL_DEBUG:
        // DBG and blue foreground
        lvl_str = "DBG";
        ansi_color = 34;
        break;

    case LOG_LEVEL_WARNING:
        // WAR and yellow foreground
        lvl_str = "WAR";
        ansi_color = 33;
        break;
    
    default:
        // NAN and white foreground
        lvl_str = "NAN";
        ansi_color = 37;
        break;
    }
    // get current time
    time_t t = time(NULL);
    // convert to localtime
    struct tm *lt = localtime(&t);
    // print message
#ifdef DISABLE_ANSI_COLOR
    printf(
        "%02d:%02d:%02d [%s] %s\n",
        lt->tm_hour, lt->tm_min, lt->tm_sec, lvl_str, msg
    );
#else
    printf(
        "%02d:%02d:%02d [\x1B[0;%dm%s\x1B[0m] %s\n",
        lt->tm_hour, lt->tm_min, lt->tm_sec, ansi_color, lvl_str, msg
    );
#endif
}

/**
 * Prepare the log message, by using sprintf to format the
 * message to finally print.
 */
char *log_prepare(const char *fmt, va_list args) {
    // allocate
    char *buf = malloc(MAX_LOG_MSG_LENGTH);
    if(buf == NULL) {
        puts("alloc failure\n");
        exit(1);
        return NULL;
    }
    // sprintf the content of the log message
    vsprintf(buf, fmt, args);
    return buf;
}

/**
 * The current log level (which is held private).
 */
log_level_e log_level = LOG_LEVEL_DEBUG;

/**
 * Shortcut to define a leveled log function. 
 */
#define LEVELED_LOG(name, lvl) \
void log_##name(const char *fmt, ...) { \
    va_list vl; \
    va_start(vl, fmt); \
    char *buf = log_prepare(fmt, vl); \
    va_end(vl); \
    log_message(lvl, buf); \
    free(buf); \
}

/**
 * Defining the different log level functions. 
 */
LEVELED_LOG(debug, LOG_LEVEL_DEBUG)
LEVELED_LOG(warning, LOG_LEVEL_WARNING)
LEVELED_LOG(error, LOG_LEVEL_ERROR)

/**
 * This is a log_error with an additional exit and halt.
 */
void log_fatal(const char* fmt, ...) {
    log_error(fmt);
    exit(1);
    for(;;);
}
