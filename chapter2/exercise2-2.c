#include <stdio.h>

#define LIM 10

/* write a loop equivalent to the one below without using && or ||:
 *
 *   for (i = 0; i < LIM - 1 && (c = getchar()) != '\n' && c != EOF)
 *       s[i] = c;
 */

int main()
{
    int i, c;
    int s[LIM];

    for (i = 0; (c = getchar()) != '\n'; ++i) {
        if (i >= LIM - 1)
            break;
        else if (c == EOF)
            break;
        s[i] = c;
    }

    int j;
    for (j = 0; j < i; ++j)
        putchar(s[j]);
}
