#include <stdio.h>
#include <string.h>

/* Extend detab and entab to accept the shorthand "entab -m +n" to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behaviour */

/* Solution required reading in -m and +n (Note: [] binds more tightly than * and ++). Then adding an extra column
 * variable to check if we are past starting column m before entabbing. */

#define DEFAULT_START_COLUMN 0
#define DEFAULT_TABSTOP 4

int c, col, blanks, m, n, mcol;

void entab();
int _atoi(char *s);

int main(int argc, char *argv[])
{
    col = blanks = mcol = 0;
    m = DEFAULT_START_COLUMN;
    n = DEFAULT_TABSTOP;

    while (--argc > 0 && ((*++argv)[0] == '-' || (*argv)[0] == '+'))
        if ((*argv)[0] == '-')
            m = _atoi(++argv[0]);
        else if ((*argv)[0] == '+')
            n = _atoi(++argv[0]);

    while ((c = getchar()) != EOF) {
        if (++mcol >= m)
            ++col;
        entab();
    }
}

void entab()
{
    int i, nb, nt;

    if (c == ' ') {
        ++blanks;
        if (mcol >= m && col % n == 0) {
            nt = blanks / n;
            nb = blanks % n;
            for (i = 0; i < nt; ++i)
                putchar('\t');
            for (i = 0; i < nb; ++i)
                putchar(' ');
            blanks = 0;
        }
    } else {
        putchar(c);
        if (c == '\n')
            col = mcol = 0;
        else if (mcol >= m && c == '\t')
            col = col + (n - (col - 1) % n) - 1;
    }
}

int _atoi(char *s)
{
    int n;

    for (n = 0; *s >= '0' && *s <= '9'; ++s)
        n = 10 * n + (*s - '0');

    return n;
}
