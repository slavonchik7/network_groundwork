


#ifndef FILE_WRAP_H
#define FILE_WRAP_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#ifdef __linux__
#include <errno.h>
#include <fcntl.h>
//#include <unistd.h>
#endif /* __linux__ */


FILE *Fopen(const char *filename, const char *modes);

long int Ftell(FILE *stream);

int Fseek(FILE *stream, long int offset, int whence);

int check_fstream(FILE *stream, const char *errmsg);

long int file_size(FILE *stream);

#endif /* FILE_WRAP_H */
