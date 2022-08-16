#include <stdio.h>

/* In a two's complement number system, x &= (x - 1) deletes the rightmost 1-bit
 * in x. Explain why. Use this observation to write a faster version of bitcount
 */

/* Explanation:
 * subtracting 1 from a value in a two's complement number system will result in
 * a new value in which the bit at the position of the previously rightmost 1
 * will be 0, all lower order bits will be switched to 1 and all higher order
 * bits left unchanged. Using this new value as a mask on the original value
 * using the & bitwise operator will result in the rightmost bit being set to 0
 * (1 & 0 == 0). All higher order bits than the rightmost bit will be masked
 * with their own value (1 & 1 or 0 & 0), leaving them unchanged. All lower
 * order bits are 0 and therefore will also be left unchanged by the mask. 
 * 
 * eg: 10 &= (10 - 1) -> 10 &= 9 -> 0b1010 &= 0b1001 -> 0b1000 == 8 
 *
 */

int bitcount(unsigned x);

int main() 
{
    unsigned x;

    //1010
    x = 10;
    //two 1 bits
    printf("%d\n", bitcount(x));
    
    //1111
    x = 15;
    //four 1 bits
    printf("%d\n", bitcount(x));

    //01
    x = 1;
    //one 1 bit
    printf("%d\n", bitcount(x));
    
    //0
    x = 0;
    //zero 1 bit
    printf("%d\n", bitcount(x));
}

int bitcount(unsigned x)
{
    int b;
    
    if (x == 0)
        return 0;
    
    for (b = 1; (x &= x - 1) != 0; ++b)
        ;

    return b;
}
