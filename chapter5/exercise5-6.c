#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good
 * possibilities include getline (chapters 1 and 4)m, atoi, itoa, and their variants (chapter 2, 3, and 4), reverse
 * (chapter 3), and strindex and getop (chapter 4). */

int _getline(char *s, int lim);
int _atoi(char *s);
void itoa_chapter3_4(int n, char *s);
void itoa_chapter3_6(int n, char *s, int width);
char *itoa_chapter4_12(int n, char *buffer);
void reverse(char *s);
void swap(char *s, char *t);
int strindex(char *s, char *t);
#define NUMBER '0' /* signal that a number was found */
int getop(char *s);

#define MAXSIZE 100

int main()
{
    char buffer[MAXSIZE];
    char *s, *t;
    int n, size, padding, type;

    /* test getline (ctrl+d to end) */
    while ((size = _getline(buffer, MAXSIZE)))
        printf("getline: read in '%s'\nsize: %d\n", buffer, size);

    /* test atoi */
    s = "123456789";
    printf("atoi: string '%s' to int: %d\n", s, _atoi(s));

    /* test itoa */
    /* chapter 3-4 version */
    n = 98754321;
    itoa_chapter3_4(n, buffer);
    printf("itoa (chapter3-4): integer %d to string: '%s'\n", n, buffer);
    itoa_chapter3_4(-n, buffer);
    printf("itoa (chapter3-4): integer %d to string: '%s'\n", -n, buffer);

    /* test itoa */
    /* chapter 3-6 version */
    padding = 20;
    itoa_chapter3_6(n, buffer, padding);
    printf("itoa (chapter3-6): integer %d to string with padding %d: '%s'\n", padding, n, buffer);
    itoa_chapter3_6(-n, buffer, padding);
    printf("itoa (chapter3-6): integer %d to string with padding %d: '%s'\n", padding, -n, buffer);

    /* test itoa */
    /* chapter 4-12 version */
    itoa_chapter4_12(n, buffer);
    printf("itoa (chapter4-12): integer %d to string: '%s'\n", n, buffer);
    itoa_chapter4_12(-n, buffer);
    printf("itoa (chapter4-12): integer %d to string: '%s'\n", -n, buffer);

    /* test reverse */
    char reversebuffer[MAXSIZE] = "reverse this string";
    printf("reverse of '%s': ", reversebuffer);
    reverse(reversebuffer);
    printf("'%s'\n", reversebuffer);

    /* test strindex */
    s = "test string for strindex";
    t = "string";
    printf("strindex: index of '%s' in '%s': %d\n", t, s, strindex(s, t));

    /* test getop */
    while ((type = getop(buffer)) != EOF)
        printf("getop: string '%s' is type is number: %d\n", buffer, type == NUMBER);
}

int _getline(char *s, int lim)
{
    int i;

    for (i = lim; i && (*s = getchar()) != EOF && *s != '\n'; --i, ++s)
        ;

    *s++ = '\0';

    return lim - i;
}

int _atoi(char *s)
{
    int n;

    for (n = 0; *s >= '0' && *s <= '9'; ++s)
        n = 10 * n + (*s - '0');

    return n;
}

/* Chapter 3-4 version adaption */
void itoa_chapter3_4(int n, char *s)
{
    int negative;
    char *t;

    t = s;

    negative = n < 0;

    do {
        *t++ = abs(n % 10) + '0';
    } while ((n /= 10));

    if (negative)
        *t++ = '-';

    *t = '\0';

    reverse(s);
}

/* Chapter 3-6 adaption: version of itoa with three arguments, third argument is min field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide enough. */
void itoa_chapter3_6(int n, char *s, int width)
{
    int i, negative;

    negative = n < 0;

    i = 0;
    do {
        *(s + i++) = abs(n % 10) + '0';
    } while ((n /= 10));

    if (negative)
        *(s + i++) = '-';

    while (i < width)
        *(s + i++) = ' ';

    *(s + i) = '\0';

    reverse(s);
}

/* Chapter 4-12: recursive version */
/* Only solution I could come up with was to change return type from void to char* so we can keep track of where we are
 * in the buffer when coming out of recursion and writing to buffer */
char *itoa_chapter4_12(int n, char *buffer)
{
    if (n < 0)
        *buffer++ = '-';

    if (n / 10)
        buffer = itoa_chapter4_12(abs(n / 10), buffer);

    *buffer++ = abs(n % 10) + '0';
    *buffer = '\0';

    return buffer;
}

void reverse(char *s)
{
    char *t;

    /* set t to end of s (before terminating '\0') */
    t = s + strlen(s) - 1;

    /* less than comparison is valid because s and t both point to locations in same character array */
    while (s < t)
        swap(s++, t--);
}

void swap(char *s, char *t)
{
    char temp;

    temp = *s;
    *s = *t;
    *t = temp;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    char *u, *v;

    while (*s != '\0') {
        u = s++;
        v = t;
        while (*u++ == *v++)
            if (*v == '\0')
                return u - s;
    }

    return -1;
}

#define BUFSIZE 100 /* size of unread character array for ungetch */

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch();
void ungetch();

/* initial version of getop from chapter4-4 */
int getop(char *s)
{
    int c;

    while ((*s++ = c = getch()) == ' ' || c == '\t')
        ;

    *s = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    if (c == '-') { /* check if negative number */
        if (!isdigit(c = getch())) {
            ungetch(c);
            return '-';
        }
        *s++ = c;
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(c = getch()))
            *s++ = c;

    if (c == '.') { /* collect fraction part */
        *s++ = c;
        while (isdigit(c = getch()))
            *s++ = c;
    }

    *s = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
