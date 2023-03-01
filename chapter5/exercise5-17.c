#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Add a field-searching capability, so sorting may be done on fields within lines, each field sorted according to an
 * independent set of options. */

/* Solution: add reading start (- then digit) position and end position (+ then digit) from command line args for where
 * in lines to apply sorting to */

#define MAXLINES 5000 /* max number of lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int _getline(char *s, int lim);

void _qsort(void *lineptr[], int left, int right, int (*comp)(const void *, const void *));
int numcmp(const char *, const char *);
int _strcmp(const char *, const char *);

int numeric;
int reverse; /* 1 if reverse sort */
int fold;
int dirorder;
int start, end; /* start and end positions of lines to sort with given options */

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    int prefix, c;
    int (*comp)(const void *, const void *); /* pointer to compare function to use */

    numeric = reverse = fold = dirorder = 0;
    start = end = 0;
    comp = (int (*)(const void *, const void *))_strcmp;

    /* read flags */
    while (--argc && (((prefix = (*++argv)[0]) == '-') || prefix == '+')) {
        if (prefix == '-') {
            printf("prefix -\n");
            if (isdigit(*(argv[0] + 1))) {
                printf("setting end\n");
                end = atoi(++argv[0]);
            } else {
                while (isalpha(c = tolower(*++argv[0]))) {
                    switch (c) {
                        case 'n':
                            numeric = 1;
                            comp = (int (*)(const void *, const void *))numcmp;
                            break;
                        case 'r':
                            reverse = 1;
                            break;
                        case 'f':
                            fold = 1;
                            break;
                        case 'd':
                            dirorder = 1;
                            break;
                        default:
                            printf("error: unknown flag %c\n", c);
                            break;
                    }
                }
            }
        } else if (prefix == '+') {
            printf("setting start\n");
            start = atoi(++argv[0]);
        }
    }

    if (start > end) {
        printf("error: start pos (%d) must be <= to end pos (%d)\n", start, end);
        return 1;
    }

    /* sort */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **)lineptr, 0, nlines - 1, comp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
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

#define MAXSUBSTR 100

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    char sstr[MAXSUBSTR];

    strncpy(sstr, s1 + start, end - start);
    v1 = atof(sstr);
    strncpy(sstr, s2 + start, end - start);
    v2 = atof(sstr);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int _strcmp(const char *s1, const char *s2)
{
    char a, b;
    int i, j;
    int strend;

    if (end > 0)
        strend = end;
    else if ((end = strlen(s1)) > strlen(s2))
        strend = strlen(s2);

    i = j = start;
    do {
        if (dirorder) {
            /* skip anything character not number, letter, blank */
            while (i < strend && !isalnum(s1[i]) && s1[i] != ' ' && s1[i] != '\0')
                ++i;

            while (j < strend && !isalnum(s2[j]) && s2[j] != ' ' && s2[j] != '\0')
                ++j;
        }

        if (i < strend && j < strend) {
            a = s1[i++];
            b = s2[j++];
        }

        if (fold) {
            a = tolower(a);
            b = tolower(b);
        }

        if (a == b && a == '\0')
            return 0;
    } while (a == b && i < strend && j < strend);

    return a - b;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
