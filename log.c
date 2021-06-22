#include "log.h"

#if !defined(LOGGER_DISABLE)
#include <stdio.h>
void ConsolePut(const char * str) {
    printf("%s", str);
}
#endif

#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
#include <stdarg.h>
void ConsolePrintf(const char * format, ...) {
    va_list arglist;
    va_start(arglist, format);
    
    switch (format[0])
    {
        // LOGGER_PRINTF_OK
        case '\1':{
            #ifdef LOGGER_COLOR
            printf("%s", "\e[1;32m");
            #endif
            
            printf("%s", "OK ");
            break;
        }
        // LOGGER_PRINTF_WRN
        case '\2':{
            #ifdef LOGGER_COLOR
            printf("%s", "\e[1;33m");
            #endif
            printf("%s", "WARRNING ");
            break;
        }
        // LOGGER_PRINTF_ERR
        case '\3':{
            #ifdef LOGGER_COLOR
            printf("%s", "\e[1;31m");
            #endif
            printf("%s", "ERROR ");
            break;
        }
    
        default: {
            format--;
            break;
        }
    }
    
    format++;
    #ifdef LOGGER_COLOR
    if (format[0] != '\4') {
        printf("%s", "\e[0m");
    }
    #endif
    
    vprintf(format, arglist);
    puts("");
    va_end(arglist);
}
#endif

struct Logger consoleLogger = {
#if !defined(LOGGER_DISABLE)
    .LPut = ConsolePut,
#endif
    
#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
    .LPrintf = ConsolePrintf
#endif
};