#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Modify the sort program to handle a -r flag, which indicates soritng in reverse (decreasing) order. Be sure that -r
 * works with -n */

/* Solution: handle r flag using same technique shown in previous (command line arguments) section of book, then use
 * reverse var to check whether to use < or > in qsort func. Also added const to compare function params to silence
 * warnings from compiler (due to strcmp in stdlib taking const params)*/

#define MAXLINES 5000 /* max number of lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int _getline(char *s, int lim);

void _qsort(void *lineptr[], int left, int right, int (*comp)(const void *, const void *));
int numcmp(const char *, const char *);

int reverse; /* 1 if reverse sort */

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    int numeric; /* 1 if numeric sort */
    int c;

    numeric = reverse = 0;

    /* read flags */
    while (--argc && (*++argv)[0] == '-') {
        while (isalpha(c = tolower(*++argv[0]))) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default:
                    printf("error: unknown flag %c\n", c);
                    break;
            }
        }
    }

    /* sort */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **)lineptr, 0, nlines - 1, (int (*)(const void *, const void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }

    printf("reverse %d, numeric %d\n", reverse, numeric);
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

/* qsort: sort v[left]..v[right] into increasing order */
void _qsort(void *v[], int left, int right, int (*comp)(const void *, const void *))
{
    int i, last, cmp;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains fewer than two elements */
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        cmp = (*comp)(v[i], v[left]);
        if (reverse ? cmp > 0 : cmp < 0)
            swap(v, ++last, i);
    }

    swap(v, left, last);
    _qsort(v, left, last - 1, comp);
    _qsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
