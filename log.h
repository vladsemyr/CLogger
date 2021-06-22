#ifndef LOG_H
#define LOG_H

#include "log_cfg.h"

struct Logger {
#if !defined(LOGGER_DISABLE)
    void (* LPut)(const char *);
#else
    #define LPut(...)     __disabledPut
    int __disabledPut;
#endif

#if !defined(LOGGER_DISABLE) && !defined(LOGGER_VA_ARGS_DISABLE)
    void (* LPrintf)(const char *format, ...);
#else
    #define LPrintf(...)  __disabledPrintf
    int __disabledPrintf;
#endif
};

extern struct Logger _consoleLogger;
#define consoleLogger (void)_consoleLogger


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define LOGGER_PRINTF_OK  "\1"
#define LOGGER_PRINTF_WRN "\2"
#define LOGGER_PRINTF_ERR "\3"

#ifdef LOGGER_COLOR
    #define LOGGER_F "\4" __FILE__ " [#" STR(__LINE__) "] \e[0m"
#else
    #define LOGGER_F __FILE__ " [#" STR(__LINE__) "] "
#endif

#define LOGGER_FULL_OK  LOGGER_PRINTF_OK  LOGGER_F
#define LOGGER_FULL_WRN LOGGER_PRINTF_WRN LOGGER_F
#define LOGGER_FULL_ERR LOGGER_PRINTF_ERR LOGGER_F

#endif