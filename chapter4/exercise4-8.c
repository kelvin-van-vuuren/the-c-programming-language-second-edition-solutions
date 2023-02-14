#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly */

/* Seems a bit simple but this answer only required changing the buffer size to 1 */

#define BUFSIZE 1 /* size of unread character array for ungetch */

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
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
