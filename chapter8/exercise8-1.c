#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <syscall.h>

/* Rewrite the program cat from chapter 7 using read, write, open and close instead of their standard library
 * equivalents. Perform exeriments to determine the relative speeds of the two versions */

void filecopy(int from, int to);
void error(char *fmt, ...);

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char *prog;

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    prog = argv[0]; /* program name for errors */
    int fd;

    if (argc == 1) {
        /* no args; copy standard input */
        filecopy(STDIN, STDOUT);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                error("%s: can't open %s", prog, *argv);
                exit(1);
            } else {
                filecopy(fd, STDOUT);
            }
        }
    }

    exit(0);
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(int from, int to)
{
    int c;
    int n;
    char buf[BUFSIZ];

    while ((n = read(from, buf, BUFSIZ)) > 0)
        if (write(to, buf, n) != n)
            error("%s: write error on file", prog);
}

/* error:  print an error message and die */
void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
