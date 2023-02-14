#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be in an EOF
 * is pushed back, then implement your design. */

/* Just added a check in ungetch which stops EOF being pushed back onto buffer. An alternative would be to change the
 * buffer data type to int and allow EOF to be pushed back. */

#define BUFSIZE 100 /* size of unread character array for ungetch */

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch();
void ungetch();
void ungets(char s[]);

main()
{
    char c = 'c';
    ungetch(c);
    printf("Unget get char '%c', getch() result after unget: %c\n", c, getch());
}

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE) {
        if (c != EOF)
            buf[bufp++] = c;
        else
            printf("ungetch error: cannot store EOF as char\n");
    } else {
        printf("ungetch: too many characters\n");
    }
}
