#include <stdio.h>

/* program fold long input lines into two or more shorter lines after the last
 * non-blank character that occurs before the n-th column of input*/

int getchar_equals(int *c, int equals);

int main()
{
    int c, quote, spaces, escaped;
    
    spaces = escaped = 0;
    
    while ((c = getchar()) != EOF) {
        
        /* handle comments */
        if (c == '/') {
            if ((c = getchar()) != EOF) {
                if (c == '/') {
                    spaces = 0;
                    while ((c = getchar()) != '\n' && c != EOF) 
                        ;
                    continue;
                } else if (c == '*') {
                    spaces = 0;
                    while (!((c = getchar() == '*' && (c = getchar()) == '/')) && c != EOF)
                        ;
                    if ((c = getchar()) == '\n') 
                        continue;
                } else {
                    putchar('/');
                }
            }
        }
        
        /* handle quotes */
        if ((quote = c) == '"' || quote == '\'') {
            putchar(c);
            while (((c = getchar()) != quote || escaped) && c != EOF) {
                escaped = !escaped && c == '\\';
                putchar(c);
            }
            if (c == quote)
                putchar(c);
            continue;
        }
        
        /* prevent spaces before a commented line being printed */
        if (c == ' ') {
            ++spaces;
            continue;
        }
        
        if (spaces > 0)
            for ( ; spaces > 0; --spaces)
                putchar(' ');
            
        putchar(c);
    }
}
