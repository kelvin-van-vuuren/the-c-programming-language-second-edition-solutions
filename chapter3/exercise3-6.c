#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* write a version of itoa that accepts three arguments instead of two. The third
 * argument is a minimum field width; the converted number must be padded with
 * blanks on the left if necessary to make it wide enough */

#define MAXLEN 1000

void itoa(int n, char s[], int width);
void reverse(char line[]);

main()
{
    int n, w;
    char s[MAXLEN];

    w = 5;
    n = 1;

    itoa(n, s, w);
    printf("%s\n", s);

    n = -10;
    itoa(n, s, w);
    printf("%s\n", s);

    n = INT_MIN;
    itoa(n, s, w);
    printf("%s\n", s);
}

void itoa(int n, char s[], int width)
{
    int i, negative;

    negative = n < 0;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (negative)
        s[i++] = '-';

    while (i < width)
        s[i++] = ' ';

    s[i] = '\0';

    reverse(s);
}

void reverse(char line[])
{
    int i, j, temp, len;

    len = strlen(line) - 1;

    for (i = 0, j = len; i <= j; ++i, --j) {
        temp = line[i];
        line[i] = line[j];
        line[j] = temp;
    }
}
