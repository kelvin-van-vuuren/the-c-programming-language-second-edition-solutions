#include <stdio.h>
#include <string.h>

/* Rewrite realines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much
 * faster is the program? */

/* I have skipped profiling the new readlines against the original from the book. The book's implementation allocated a
 * new array of length MAXLEN each time a line was being read. By allocating a single array in main, then passing this
 * to readlines for it to store input into, we avoid multiple allocations of size MAXLEN. This is a more efficient
 * approach. */

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines, char *line);
int _getline(char *s, int lim);
void writelines(char *lineptr[], int nlines);

int main()
{
    int nlines;
    char lines[MAXLINES * MAXLEN]; /* allocate storage for max possible number of chars */

    if ((nlines = readlines(lineptr, MAXLINES, lines)) >= 0) {
        printf("Writing lines:\n");
        writelines(lineptr, nlines);
    } else {
        printf("error: input exceed max lines\n");
        return 1;
    }
}

/* new version */
int readlines(char *lineptr[], int maxlines, char *lines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    /* set p to first free character in main's array */
    p = lines + strlen(lines);

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0) {
        /* do not need to check if p valid because will only be invalid if nlines >= maxlines */
        if (nlines >= maxlines) {
            return -1;
        } else {
            /* delete new line */
            line[len - 1] = '\0';
            /* copy line to storage p is pointing to */
            strcpy(p, line);
            /* set lineptr for current line to p */
            lineptr[nlines++] = p;
            /* move p to next free position */
            p += len;
        }
    }

    return nlines;
}

int _getline(char *s, int lim)
{
    int i;

    for (i = lim; i && (*s = getchar()) != EOF && *s != '\n'; --i, ++s)
        ;

    *s++ = '\0';

    return lim - i;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
