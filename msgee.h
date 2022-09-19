

#ifndef MSGEE_H
#define MSGEE_H

#include <stdlib.h>


#define EXIT_WITH_LOG_ERROR(ehandler, ehdata, m, err) \
            do { \
                fflush(stderr); \
                fprintf(stderr, "(FILE: %s, LINE: %d, func: %s)", __FILE__, __LINE__, __func__); \
                fflush(stderr); \
                exit_with_error(ehandler, ehdata, m, err); \
            } while(0)


void exit_with_error(void ehandler(void *), void *ehdata,
        const char *m, int err);

#endif /* MSGEE_H */
