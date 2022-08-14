#include <stdio.h>

/* function setbits(x, p, n, y) that returns x with the n bits that begin at
 * position p set to the rightmost n bits of y, leaving the other bits unchanged
 */

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);

int main()
{
    //11001111 = 128 + 64 + 8 + 4 + 2 + 1
    unsigned x = 207;
    
    //00000011 = 2 + 1
    unsigned y = 3;
    
    //11111111 = 255
    printf("%d\n", setbits(x, 5, 2, y));

    x = 0;
    
    //11 = 3
    printf("%d\n", setbits(x, 1, 2, y));

    //11111111 = 128 + 64 + 32 + 16 + 8 + 4 + 2 + 1
    x = 255;
    
    //00000000
    y = 0;

    //11001111 = 207
    printf("%d\n", setbits(x, 5, 2, y));
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned y_rightmost_n_bits = getbits(y, n - 1, n);
    unsigned clear_target_bit_field = x & ~(~(~0 << n ) << (p + 1 - n));
    unsigned shifted_rightmost_bits = y_rightmost_n_bits << (p + 1 - n);
    
    return clear_target_bit_field | shifted_rightmost_bits;
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);  
}
