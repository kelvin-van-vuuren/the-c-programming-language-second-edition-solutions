#include <stdio.h>

/* function invert(x, p, n) that returns x with the n bits that begin at
 * position p inverted, leaving the others unchanged
 */

unsigned invert(unsigned x, int p, int n);

int main()
{
    //11001111 = 128 + 64 + 8 + 4 + 2 +1
    unsigned x = 207;
    
    //11111111 = 255
    printf("%d\n", invert(x, 5, 2));
    
    //invert back
    x = 255;
    printf("%d\n", invert(x, 5, 2));
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = ~(~0 << n) << (p + 1 - n);
    return x ^ mask;
}
