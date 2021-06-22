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

#define LOGGER_END_COLOR "\e[0m"

#define LOGGER_START_RED "\e[1;31m"
#define LOGGER_END_RED LOGGER_END_COLOR
#define LOGGER_RED(x) LOGGER_START_RED x LOGGER_END_RED

#define LOGGER_START_GREEN "\e[1;32m"
#define LOGGER_END_GREEN LOGGER_END_COLOR
#define LOGGER_GREEN(x) LOGGER_START_GREEN x LOGGER_END_GREEN

#define LOGGER_START_YELLOW "\e[1;33m"
#define LOGGER_END_YELLOW LOGGER_END_COLOR
#define LOGGER_YELLOW(x) LOGGER_START_YELLOW x LOGGER_END_YELLOW


#define LOGGER_PRINTF_OK  LOGGER_GREEN("OK ")
#define LOGGER_PRINTF_WRN LOGGER_YELLOW("WARRNING ")
#define LOGGER_PRINTF_ERR LOGGER_RED("ERROR ")

#define LOGGER_F __FILE__ ":" STR(__LINE__) ":\n    "

#define LOGGER_FULL_OK  LOGGER_PRINTF_OK  LOGGER_F
#define LOGGER_FULL_WRN LOGGER_PRINTF_WRN LOGGER_F
#define LOGGER_FULL_ERR LOGGER_PRINTF_ERR LOGGER_F


#ifndef LOGGER_COLOR

    #undef LOGGER_END_COLOR
    #undef LOGGER_START_RED
    #undef LOGGER_END_RED
    #undef LOGGER_RED
    #undef LOGGER_START_GREEN
    #undef LOGGER_END_GREEN
    #undef LOGGER_GREEN
    #undef LOGGER_START_YELLOW
    #undef LOGGER_END_YELLOW
    #undef LOGGER_YELLOW

    #define LOGGER_END_COLOR
    #define LOGGER_START_RED
    #define LOGGER_END_RED
    #define LOGGER_RED(x) x
    #define LOGGER_START_GREEN
    #define LOGGER_END_GREEN
    #define LOGGER_GREEN(x) x
    #define LOGGER_START_YELLOW
    #define LOGGER_END_YELLOW
    #define LOGGER_YELLOW(x) x

#endif


#endif