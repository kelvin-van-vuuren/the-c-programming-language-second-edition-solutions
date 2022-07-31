#include <stdio.h>
#define TABSTOP 4

/* program detab that replaces tabs in the input with the proper number of blanks to space to the next stop. Assume a fixed set of tab stops every n columns */

int c, col;

void detab();

int main()
{
    col = 0;
    while ((c = getchar()) != EOF)
        detab();
}

void detab()
{
    int i;
    if (c == '\t') {
        for (i = 0; i < TABSTOP - col; ++i)
            putchar(' ');
        col = 0;
     } else {
        putchar(c);
        if (c == '\n')
            col = 0;
     }
     if (++col == TABSTOP)
         col = 0;
}
