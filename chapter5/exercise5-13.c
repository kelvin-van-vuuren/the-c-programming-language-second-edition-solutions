#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it
 * can be changed by an optional argument so that 'tail -n' prints the last n lines. The program should behave
 * rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of
 * available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
 * fixed size. */

/* Solution required reading in -n where n is the number of lines to print from the end of the input. Lines stored using
 * readlines and storage method from Section 5.6. Once lines have been read in, calculate which index of lineptr array
 * to start printing lines from. Use MAX macro to avoid starting index going below 0. */

#define DEFAULTLINES 10 /* default last number of lines to print */
#define MAXLINES 5000 /* max lines that can be read in */

#define MAX(a, b) ((a) > (b)) ? (a) : (b)

int _atoi(char *s);
int readlines(char *lineptr[], int nlines);
int _getline(char *s, int lim);

int n; /* last n lines of input lines read to print */
char *lineptr[MAXLINES]; /* pointers to text lines */

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */

    n = DEFAULTLINES;
    while (--argc && ((*++argv)[0] == '-')) {
        if (!(n = _atoi(++argv[0]))) {
            printf("error: invalid value for lines to print\n");
            return 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
        for (n = MAX(nlines - n, 0); n < nlines; ++n)
            printf("%s\n", lineptr[n]);

    return 0;
}

int _atoi(char *s)
{
    int n;
    for (n = 0; *s >= '0' && *s <= '9'; ++s)
        n = 10 * n + (*s - '0');

    return n;
}

#define MAXLEN 1000 /* max length of any input line */

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
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
