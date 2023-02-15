#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Adapt the ideas of printd to write a recursive version of ita; that is, convert an integer into a string by calling a
 * recursive routine */

/* Implemented using similar structure to printd. Use absolute value of n % 10 when converting from integer to char to
 * which allows INT_MIN to be handled correctly (same solution from exercise 3-4). */

#define BUFSIZE 100
#define VALSIZE 4

void printd(int n)
{
    if (n > 0) {
        putchar('-');
        n = -n;
    }

    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

void itoa(int n, char buffer[]);

int main()
{
    char buffer[BUFSIZE];
    int i, n;

    int values[VALSIZE] = {INT_MIN, INT_MAX, 0, 892347};
    for (i = 0; i < VALSIZE; ++i) {
        n = values[i];
        itoa(n, buffer);
        printf("itoa(%d) result: %s\n", n, buffer);
    }
}

void itoa(int n, char buffer[])
{
    int i;

    buffer[0] = '\0';

    if (n < 0) {
        buffer[0] = '-';
        buffer[1] = '\0';
    }

    if (n / 10)
        itoa(n / 10, buffer);

    i = strlen(buffer);
    buffer[i] = abs(n % 10) + '0';
    buffer[++i] = '\0';
}
