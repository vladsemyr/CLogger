#include "log.h"

#ifdef LOGGER_TIME
#include <time.h>
#include <stdio.h>

static void PrintTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    #ifdef LOGGER_COLOR
        printf("\e[1;30m%02d:%02d:%02d \e[0m", tm.tm_hour, tm.tm_min, tm.tm_sec);
    #else
        printf("%02d:%02d:%02d ", tm.tm_hour, tm.tm_min, tm.tm_sec);
    #endif
}

#else
#define PrintTime()
#endif

#if !defined(LOGGER_DISABLE)
#include <stdio.h>
void ConsolePut(const char * str) {
    PrintTime();
    puts(str);
}
#endif

#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
#include <stdarg.h>
void ConsolePrintf(const char * format, ...) {
    va_list arglist;
    va_start(arglist, format);
    PrintTime();
    vprintf(format, arglist);
    puts("");
    va_end(arglist);
}
#endif

struct Logger _consoleLogger = {
#if !defined(LOGGER_DISABLE)
    .LPut = ConsolePut,
#endif
    
#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
    .LPrintf = ConsolePrintf
#endif
};