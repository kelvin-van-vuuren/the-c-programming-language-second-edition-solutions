#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

/* The standard library function fseek is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and return value is an int status, not a position. Write fseek. Make sure that your fseek coordinates
 * properly with the buffering done for the other functions of the library. */

enum _flags
{
    _READ = 01, /* file open for reading */
    _WRITE = 02, /* file open for writing */
    _UNBUF = 04, /* file is unbuffered */
    _EOF = 010, /* EOF has occurred on this file */
    _ERR = 020 /* error occurred on this file */
};

typedef struct _iobuf
{
    int cnt; /* characters left */
    char *ptr; /* next character position */
    char *base; /* location of buffer */
    int flag; /* mode of file access */
    int fd; /* file descriptor */
} _FILE;

int _fseek(_FILE *fp, long offset, int origin)
{
    int rc, n;

    rc = 0;
    if (fp->flag & _READ) {
        if (origin == 1) /* if from current position */
            offset -= fp->cnt;
        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0;
    } else if (fp->flag & _WRITE) {
        if ((n = fp->ptr - fp->base) > 0)
            if (write(fp->fd, fp->base, n) != n)
                rc = -1;
        if (rc != -1)
            rc = lseek(fp->fd, offset, origin);
    }

    return rc != -1 ? 0 : -1;
}
