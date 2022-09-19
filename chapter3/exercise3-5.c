#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* write the function itob(n, s, b) that converts the integer n into a base b
 * character representation in the string s. In particular, itob(n, s, 16)
 * formats n as a hexadecimal integer in s */


/* base conversion can be done by dividing n by the base, storing the remainder,
 * repeating until n == 0, then reversing the order of the sequence of
 * remainders. Each time the remainder is stored this will need to be converted
 * into a character, this is done using the function itoc. Bases 2 - 10 will use
 * digits 0 - 1 / 9. Bases greater than this will start to use characters from
 * the modern latin alphabet starting from 'a'. Hence if n is > 9 in the
 * function itoc, then the value returned is n + 'a' - 10. This relies on the
 * fact that the ASCII values for a...z are sequential.*/

#define MAXLEN 1000

void itob(int n, char s[], int b);
char itoc(int n);
void reverse(char line[]);

main()
{
    int n, b;
    char s[MAXLEN];

    n = b = 16;
    itob(n, s, b);

    printf("%d to base %d is: %s\n", n, b, s);
    
    n = -16;
    itob(n, s, b);
    printf("%d to base %d is: %s\n", n, b, s);

    n = 31;
    b = 32;
    itob(n, s, b);
    printf("%d to base %d is: %s\n", n, b, s);

}

void itob(int n, char s[], int b)
{
    int i, negative;
    
    negative = n < 0;
    
    i = 0;
    do {
        s[i++] = itoc(abs(n % b));
    } while ((n /= b) != 0);
    
    if (negative)
        s[i++] = '-';
        
    s[i] = '\0';
    
    reverse(s);
}

char itoc(int n)
{
    if (n <= 9)
        return n + '0';

    return n + 'a' - 10;
}

void reverse(char line[]) 
{
    int i, j, temp, len;

    len = strlen(line) - 1;
    
    for (i = 0, j = len; i <= j; ++i, --j) {
        temp = line[i];
        line[i] = line[j];
        line[j] = temp;
    }
}
