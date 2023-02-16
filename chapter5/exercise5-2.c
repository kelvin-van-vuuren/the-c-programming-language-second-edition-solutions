#include <ctype.h>
#include <stdio.h>

/* Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? */

/* getfloat return type is int, just like get int. This is because the return value is only used to indicate a status
 * code, in this case whether the input read is EOF or whether or not the input read was a number. Implementation only
 * required a simple addition to getint to check for and collect fractional parts of input. */

#define NOT_NUMBER 0

int getfloat(float *pn);

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch();
void ungetch(int c);

void main()
{
    int rc;
    float pf;

    while ((rc = getfloat(&pf)) != EOF)
        if (rc == NOT_NUMBER)
            printf("getfloat: Not a number\n");
        else
            printf("getfloat: number, pf = %f\n", pf);
}

int getfloat(float *pf)
{
    int c, sign, temp;
    float power;

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

    /* collect integer part */
    for (*pf = 0; isdigit(c); c = getch())
        *pf = 10 * *pf + (c - '0');

    /* collect fraction part */
    if (c == '.')
        for (c = getch(), power = 10; isdigit(c); c = getch(), power *= 10)
            *pf = *pf + (c - '0') / power;

    *pf *= sign;

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
