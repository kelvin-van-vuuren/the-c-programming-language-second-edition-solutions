#include <stdio.h>

#define N_ASCII_CHAR 256 /* Number of characters in extended ASCII character set */

/* program to print a histogram of the frequencies of different characters in its input */

int main()
{
    int c, i, j;
    int frequencies[N_ASCII_CHAR];

    for (i = 0; i < N_ASCII_CHAR; ++i)
        frequencies[i] = 0;

    while ((c = getchar()) != EOF)
        ++frequencies['c'];

    printf(" ASCII code | frequency\n");
    for (i = 0; i < N_ASCII_CHAR; ++i) {
        printf("      %5d | ", i);
        for (j = 0; j < frequencies[i]; ++j)
            putchar('+');
        putchar('\n');
    }
}
