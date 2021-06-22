#include "log.h"

#if !defined(LOGGER_DISABLE)
#include <stdio.h>
void ConsolePut(const char * str) {
    puts(str);
}
#endif

#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
#include <stdarg.h>
void ConsolePrintf(const char * format, ...) {
    va_list arglist;
    va_start(arglist, format);
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