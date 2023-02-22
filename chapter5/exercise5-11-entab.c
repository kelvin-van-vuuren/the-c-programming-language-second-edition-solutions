#include <stdio.h>

/* Modify the program entab (written as an exercise in chapter 1) to accept a list of tab stops as arguments. Use the
 * default tab settings if there are no arguments. */

#define DEFAULT_TABSTOP 4

int _atoi(char *s);

int main(int argc, char *argv[])
{
    int c, i, nb, nt, col, blanks, tabstop;

    col = 0;
    tabstop = (--argc > 0) ? _atoi(*++argv) : DEFAULT_TABSTOP;

    while ((c = getchar()) != EOF) {
        ++col;
        if (c == ' ') {
            ++blanks;
            if (col % tabstop == 0) {
                nt = blanks / tabstop;
                nb = blanks % tabstop;
                for (i = 0; i < nt; ++i)
                    putchar('\t');
                for (i = 0; i < nb; ++i)
                    putchar(' ');
                blanks = 0;
                tabstop = (--argc > 0) ? _atoi(*++argv) : DEFAULT_TABSTOP;
            }
        } else {
            putchar(c);
            if (c == '\n') {
                col = 0;
            } else if (c == '\t') {
                col = col + (tabstop - (col - 1) % tabstop) - 1;
            }
        }
    }
}

int _atoi(char *s)
{
    int n;

    for (n = 0; *s >= '0' && *s <= '9'; ++s)
        n = 10 * n + (*s - '0');

    return n;
}
