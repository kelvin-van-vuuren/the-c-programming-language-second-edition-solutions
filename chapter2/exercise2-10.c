#include <stdio.h>

/* function lower, which converts upper case letters to lower case, rewritten
 * with a conditional expression instead of if-else */

int lower(int c);

int main()
{
    int c = 'K';
   printf("%c\n", (char)lower(c));

    c = 'c';
    printf("%c\n", (char)lower(c));
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
