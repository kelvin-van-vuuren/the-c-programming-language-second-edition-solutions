#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* in a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to
 * -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs. */

/* the original function relied on flipping the sign of the integer n if it was
 * negative. ie:
 *
 * if ((sign = n) < 0)
 *   n = -n;
 *
 * However, the largest negative number does not have a positive representation
 * due to the range of a two's complement integer being -(2^(wordsize-1)) to
 * 2^(wordsize-1)-1. Therefore, INT_MIN *= -1 == INT_MIN. eg, if wordsize == 4:
 * Therefore, INT_MIN *= -1 == INT_MIN. eg, if wordsize == 4:
 *          11111000 (-128 + 64 + 32 + 16 + 8 + 0 + 0 + 0 = -8)
 * x        11111111 (-128 + 64 + 32 + 16 + 8 + 4 + 2 + 1 = -1)
 * _________________
 *      111111111000
 *      11111111000x
 *      1111111000xx
 *      111111000xxx
 *      11111000xxxx
 *     11111000xxxxx
 *    11111000xxxxxx
 *   11111000xxxxxxx
 * _________________
 *       00000001000 (only need 8 least significant bits)
 * = 00001000 = 8
 * However, since wordsize = 4 this gets truncated to 1000 which is -8.
 *
 * Since INT_MIN *= -1 == INT_MIN, the modulo operation will return a negative
 * digit. 
 * Converting a single integer digit to its char equivalent relies on the
 * fact that the ASCII values for digits 0-9 are sequential. ie: '0' == 48, '1'
 * == 49 ... '9' == 57, hence 1 + '0' = 49 == '1'.
 * Adding the integer ASCII value for the character '0' to a negative digit will 
 * not produce the correct value for that digit's character. eg -1 + '0' = 47 
 * which represents '/' in ASCII.
 *
 * We can solve this problem by taking the absolute value of n % 10 and omitting
 * the "n = -n" if n < 0. This also means we need to change the condition of the
 * while loop from (n /= 10) > 0 to (n /= 10) != 0.
 *
 */

#define MAXLEN 1000

void itoa(int n, char s[]);
void reverse(char line[]);

main() 
{
    int n;
    char s[MAXLEN];

    n = INT_MIN;
    
    itoa(n, s);
    printf("%s\n", s);
}

void itoa(int n, char s[]) 
{
    int i, negative;

    negative = n < 0;

    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (negative)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s);
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
