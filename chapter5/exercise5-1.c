#include <ctype.h>
#include <stdio.h>

/* As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a
 * character back on the input. */

/* Implementation required addition of an extra variable to check if the value of character after occurence of '+' or
 * '-' was a digit. This is necessary because if the next character is not a digit, we need to unget both this character
 * and the '-' or '+'. */

#define NOT_NUMBER 0

int getint(int *pn);

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch();
void ungetch(int c);

void main() 
{ 
    int pn, rc;
    
    while ((rc = getint(&pn)) != EOF)
        if (rc == NOT_NUMBER)
            printf("getint: Not a number\n");
        else
            printf("getint: number, pn = %d\n", pn);
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign, temp;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return NOT_NUMBER;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        temp = c;
        if (!isdigit((c = getch()))) {
            ungetch(c);
            ungetch(temp);
            return NOT_NUMBER;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
