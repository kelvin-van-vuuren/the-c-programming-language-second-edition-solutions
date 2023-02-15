#include <limits.h>
#include <stdio.h>

/* function rightrot(x, n) that returns the value of the integer x rotated to
 * the right by n bit positions
 */

#define UNSIGNED_BITS sizeof(unsigned) * CHAR_BIT

unsigned rightrot(unsigned x, int n);
unsigned getbits(unsigned x, int p, int n);

int main()
{
    unsigned x;

    printf("n bits in unsigned int: %lu\n", UNSIGNED_BITS);

    // 00000000 00000000 00000000 11001111
    x = 207;

    // 11110000 00000000 00000000 00001100 = 4026531852
    printf("%u\n", rightrot(x, 4));

    // 00000000 10000000 00000000 11111111 = 8388863
    x = 8388863;

    // 11111111 00000000 10000000 00000000 = 4278222848
    printf("%u\n", rightrot(x, 8));
}

unsigned rightrot(unsigned x, int n)
{
    unsigned rotate = getbits(x, n - 1, n);
    unsigned mask = rotate << (UNSIGNED_BITS - n);

    return (x >> n) | mask;
}

unsigned getbits(unsigned x, int p, int n) { return (x >> (p + 1 - n)) & ~(~0 << n); }
