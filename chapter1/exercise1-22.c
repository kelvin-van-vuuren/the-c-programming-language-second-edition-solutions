#include <stdio.h>
#define LINELENGTH 10

/* program fold long input lines into two or more shorter lines after the last
 * non-blank character that occurs before the n-th column of input*/

int main()
{
    int c, col, blanks;
    
    col = blanks = 0;
    while ((c = getchar()) != EOF) {
        ++col;
        if (c == '\n') {
            putchar(c);
            col = 0;
        } else {
            if (col > LINELENGTH) {
                while (c == ' ' || c == '\t')
                    c = getchar();
                putchar('\n');
                putchar(c);
                col = 1;
            } else {
                putchar(c);
            }
        }
    }
}
