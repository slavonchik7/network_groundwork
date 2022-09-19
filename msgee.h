

#ifndef MSGEE_H
#define MSGEE_H

#include <stdlib.h>
#include <stdio.h>


/*
 * the macro prints the file name, the function name and the line number
 * in which the macro is called, after which it calls the exit_with_error() function
 */
#define EXIT_WITH_LOG_ERROR(ehandler, ehdata, m, err) \
            {do { \
                fprintf(stderr, "(FILE: %s, LINE: %d, func: %s)", __FILE__, __LINE__, __func__); \
                fflush(stderr); \
                exit_with_error(ehandler, ehdata, m, err); \
            } while(0);}


/*
 * the function outputs the message "m" to the stderr stream
 * and calls the ehandler function, passing it ehdata if ehandler is not NULL
 */
void exit_with_error(void ehandler(void *), void *ehdata,
        const char *m, int err);

#endif /* MSGEE_H */
