#include <ctype.h>
#include <stdio.h>

/* Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphics
 * characters in octal or hexadecimal according to local custom, and break long text lines */

/* Solution:
 * - Go through each character from input and check if printable or non-graphic
 * - Depending on character type, increment column position accordingly
 * - If column goes over max line length, print a new line and reset column pos
 * - If control character print as hexadecimal  with precision of 2 and 0x prefix
 */

#define MAXLINE 100 /* maximum length of a line */
#define TAB 4

int column = 0;
void print(int c); /* print character and keep track of column + MAXLINE */

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (isprint(c)) {
            ++column;
            if (column > MAXLINE - 1) {
                putchar('\n');
                column = 1;
            }
            putchar(c);
        } else {
            /* non-graphic character */
            if (c == '\n') {
                column = 0;
            } else if (c == '\t') {
                column += TAB;
            } else {
                column += 4;
            }

            if (column > MAXLINE - 1) {
                putchar('\n');
                column = c == '\t' ? TAB : 4;
            }

            /* print as octal */
            printf("0x%x.2", c);
        }
    }
}
