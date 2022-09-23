

#include "file_wrap.h"





FILE *Fopen(const char *filename, const char *modes) {
    FILE *fp;

    assert(filename && modes);

    if ( (fp = fopen(filename, modes)) == NULL ) {
        fprintf(stderr,
            "cannot open file: \"%s\", with modes: \"%s\", error val: %d, msg: \"%s\"\n",
            filename, modes, errno, strerror(errno));
        exit(1);
    }

    return fp;
}



long int Ftell(FILE *stream) {
    int flen;

    assert(stream);

#ifndef __linux__
    /* if the condition is met,
     * then the file was not previously opened */
    if ( fcntl(fileno(stream), F_GETFL) == EBADF ) {
        fprintf(stderr, "in function: \"%s\", file was not previously opened\n", __func__);
        exit(1);
    }
#endif /* __linux__ */

    flen = ftell(stream);

    if (flen == -1) {
        fprintf(stderr, "error occurred ftell()\n");

        if ( fclose(stream) == EOF )
            fprintf(stderr, "cannot close file handler\n");

        exit(1);
    }

    return flen;
}

int Fseek(FILE *stream, long int offset, int whence) {
    int fskret;

    assert(stream);

#ifndef __linux__
    /* if the condition is met,
     * then the file was not previously opened */
    if ( fcntl(fileno(stream), F_GETFL) == EBADF ) {
        fprintf(stderr, "in function: \"%s\", file was not previously opened\n", __func__);
        exit(1);
    }
#endif /* __linux__ */

    fskret = fseek(stream, offset, whence);

    check_fstream(stream, "fseek() failed");

    return fskret;
}


int check_fstream(FILE *stream, const char *errmsg) {

    assert(stream);

    if ( ferror(stream) ) {
        fprintf(stderr,
            "in function: \"%s\", msg \"%s\"\n",
            errmsg, __func__);

        if ( fclose(stream) == EOF)
            fprintf(stderr,
                "cannot close file handler, error val: %d, msg: \"%s\"\n",
                errno, strerror(errno));

        exit(1);
    }

    return 0;
}

long int file_size(FILE *stream) {
    long int flen;

    Fseek(stream, 0, SEEK_END);

    flen = Ftell(stream);

    Fseek(stream, 0, SEEK_SET);

    return flen;
}
