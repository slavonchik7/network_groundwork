
#include "msgee.h"
#include "msgdefs.h"


void exit_with_error(void ehandler(void *), void *ehdata,
        const char *m, int err) {

    if(m)
        fprintf(stderr, "msg: \"%s, errnum: %d\"\n", m, err);

    if(ehandler)
        ehandler(ehdata);

    exit(err);
}
