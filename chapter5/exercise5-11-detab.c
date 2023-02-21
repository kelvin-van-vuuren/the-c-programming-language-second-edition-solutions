#include <stdio.h>

/* Modify the program detab (written as an exercise in chapter 1) to accept a list of tab stops as arguments. Use the
 * default tab settings if there are no arguments. */

/* Solution requires checking tabstop value each time a detab is performed. If there is an argument in the arg list it
 * is passed to atoi to convert to integer and the argv pointer is incremented. Else will be set to default constant. If
 * argument is not a valid integer atoi will return zero. */

/* Run using: ./a.out 3 8 12 16 < exercise5-11-detab.c.input > exercise5-11-detab.c.output
 * replace putchar(' ') with putchar('_') to more easily see effect */

#define DEFAULT_TABSTOP 4

int _atoi(char *s);

int main(int argc, char *argv[])
{
    int c, i, col, tabstop;

    col = 0;
    tabstop = (--argc > 0) ? _atoi(*++argv) : DEFAULT_TABSTOP;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (i = 0; i < tabstop - col; ++i)
                putchar(' ');
            col = 0;
            tabstop = (--argc > 0) ? _atoi(*++argv) : DEFAULT_TABSTOP;
        } else {
            putchar(c);
            if (c == '\n' || ++col == tabstop)
                col = 0;
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
