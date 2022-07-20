#include <stdio.h>

/* copy input to output, replacing each string of one or more blanks by a single blank */
int main()
{
    int blank, c;

    blank = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!blank) {
                blank = 1;
                putchar(c);
            }
        } else {
            blank = 0;
            putchar(c);
        }
    }
}
