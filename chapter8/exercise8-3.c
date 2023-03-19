#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>

/* Design and write flushbuf, fflush and fclose */

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
    int flag; /* mode of file access */
    int fd; /* file descriptor */
} _FILE;

extern _FILE _iob[OPEN_MAX];

int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
_FILE *_fopen(char *name, char *mode);
int _fflush(_FILE *fp);
int _fclose(_FILE *fp);

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

    if ((fp->flag & (_READ | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
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
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break; /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int _flushbuf(int x, _FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    } else if (write(fp->fd, fp->ptr, bufsize) != bufsize) {
        fp->flag &= _ERR;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;

    return (*fp->ptr++ = x);
}

int _fflush(_FILE *fp)
{
    int rc;

    if (fp < _iob || fp >= _iob + OPEN_MAX)
        return EOF;

    if ((fp->flag & _WRITE) && fp->base)
        rc = _flushbuf(0, fp);

    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    return rc;
}

int _fclose(_FILE *fp)
{
    int rc;

    if (fp->flag & _WRITE)
        rc = _fflush(fp);

    if (fp->base)
        free(fp->base);

    fp->flag = 0;

    return close(fp->fd) == -1 ? EOF : rc;
}
