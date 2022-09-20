

#ifndef MSGDEFS_H
#define MSGDEFS_H

#include <stdio.h>
#include <stdarg.h>


#ifndef DEBUG_LOG
#define DEBUG_LOG
#endif /* DEBUG_LOG */

#ifdef DEBUG_LOG
#define LOG_PRINT(file, ...)  \
    do { \
            fprintf(file, "(FILE: %s, LINE: %d, func: %s) msg: \"", __FILE__, __LINE__, __func__); \
            fprintf(file, __VA_ARGS__); \
            fprintf(file, "\"\n"); \
            fflush(file); \
    } while (0);
#else
#define LOG_PRINT(file, ...)
#endif /* DEBUG_LOG */

#define LOG_ERR(...) LOG_PRINT(stderr, ##__VA_ARGS__)
#define LOG_OUT(...) LOG_PRINT(stdout, ##__VA_ARGS__)




#ifdef DEBUG_LOG
#define LOG_PRINT_FRMT(file, frmt, ...)  \
    do { \
            fprintf(file, "(FILE: %s, LINE: %d, func: %s) msg: \""frmt"\"\n", \
                    __FILE__, __LINE__, __func__, \
                    __VA_ARGS__); \
            fflush(file); \
    } while (0);
#else
#define LOG_PRINT_FRMT(file, frmt, ...)
#endif /* DEBUG_LOG */

#define LOG_ERR_FRMT(frmt, ...) LOG_PRINT_FRMT(stderr, frmt, ##__VA_ARGS__)
#define LOG_OUT_FRMT(frmt, ...) LOG_PRINT_FRMT(stdout, frmt, ##__VA_ARGS__)




#endif /* MSGDEFS_H */

