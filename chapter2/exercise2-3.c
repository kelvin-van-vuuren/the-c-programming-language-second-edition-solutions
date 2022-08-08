#include <stdio.h>
#include <ctype.h>

/* function htoi(s), which converts a string of hexadecimal digits (including
 * optional 0x or 0X) into its equivalent integer values */

int htoi(char s[]);

int main()
{
    char s[5] = "0x2F";
    printf("%s (base 16) = %d (base 10)", s, htoi(s));
}

int htoi(char s[])
{
    int n, c, i;

    i = (s[0] == '0' && tolower(s[1]) == 'x') ? 2 : 0;
    
    while (isdigit(c = tolower(s[i++])) || (c >= 'a' && c <= 'f')) {
        if (c >= 'a' && c <= 'f')
            c = 10 + c - 'a'; 
        else 
            c = c - '0';

        n = 16 * n + c;
    }

    return n;
}
