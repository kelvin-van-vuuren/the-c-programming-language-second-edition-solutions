#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, word, and characters in input */

int main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/*
 * Q. How would you test the word count program? What kinds of input are most
 * likely to uncover bugs if there are any?
 *
 * A. test using a series of input files containing different combinations and
 * amount of words, whitespace and symbols. A. bugs can occur due to the program
 * treating everything that is delimited by whitespace as a word, including
 * symbols. This means that character combinations such as )*$# and 1b34 would
 * be treated as words.
 *
 */
