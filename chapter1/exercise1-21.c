#include <stdio.h>
#define TABSTOP 4

/* program entab that replaces tabs in the input with the proper number of blanks to space to the next tab stop */

int c, col, blanks;

void entab();

int main()
{
    col = blanks = 0;
    while ((c = getchar()) != EOF) {
        ++col;
        entab();
    }
}

void entab()
{
    int i, nb, nt;

    if (c == ' ') {
        ++blanks;
        if (col % TABSTOP == 0) {
            nt = blanks / TABSTOP;
            nb = blanks % TABSTOP;
            for (i = 0; i < nt; ++i)
                putchar('\t');
            for (i = 0; i < nb; ++i)
                putchar(' ');
            blanks = 0;
        }
    } else {
        putchar(c);
        if (c == '\n')
            col = 0;
        else if (c == '\t')
            col = col + (TABSTOP - (col - 1) % TABSTOP) - 1;
    }
}
