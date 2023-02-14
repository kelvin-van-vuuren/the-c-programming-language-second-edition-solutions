#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and
 * bufp, or should it just use ungetch? */

#define BUFSIZE 100 /* size of unread character array for ungetch */

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch();
void ungetch();
void ungets(char s[]);

main()
{
    char s[] = "unget this string\n";

    /* ungets should put onto buffer */
    ungets(s);

    /* now should be able to loop getch to read the string from buffer */
    while (bufp > 0)
        putchar(getch());
}

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}

void ungets(char s[])
{
    int i, len;

    len = strlen(s);

    if ((bufp + len) < BUFSIZE)
        for (i = len - 1; i >= 0; --i)
            ungetch(s[i]);
    else
        printf("ungets error: not enough space of buffer to fit string '%s'\n", s);
}
