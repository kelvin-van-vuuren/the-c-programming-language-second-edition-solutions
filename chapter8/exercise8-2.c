#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>

/* Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code and execution speed. */

/* Solution: replace FILE flag field with individual fields for each flag. Size can be reduced using chars for each flag
 * instead of int. However, still takes up more space than using a single int. */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

typedef struct _iobuf
{
    int cnt; /* characters left */
    char *ptr; /* next character position */
    char *base; /* location of buffer */
    // int flag; /* mode of file access */
    char read;
    char write;
    char unbuffered;
    char eof;
    char err;
    int fd; /* file descriptor */
} _FILE;

extern _FILE _iob[OPEN_MAX];

int _fillbuf(_FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flag & _EOF) != 0)
#define ferror(p)   ((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putcher(x) putc((x), stdout)
enum _flags
{
    _READ = 01, /* file open for reading */
    _WRITE = 02, /* file open for writing */
    _UNBUF = 04, /* file is unbuffered */
    _EOF = 010, /* EOF has occurred on this file */
    _ERR = 020 /* error occurred on this file */
};

int main() {}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(_FILE *fp)
{
    int bufsize;

    if (fp->read && !fp->eof)
        return EOF;
    bufsize = (fp->unbuffered) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->eof = 1;
        else
            fp->err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

#define PERMS 0666 /* RW for owner, group, others */

_FILE *_fopen(char *name, char *mode)
{
    int fd;
    _FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->read && !fp->write)
            break; /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        if (*mode == 'w')
            fd = creat(name, PERMS);
        else if (*mode == 'a') {
            if ((fd = open(name, O_WRONLY, 0)) == -1)
                fd = creat(name, PERMS);
            lseek(fd, 0L, 2);
        } else
            fd = open(name, O_RDONLY, 0);
    if (fd == -1) /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->read = 1;
    else
        fp->write = 1;
    return fp;
}
