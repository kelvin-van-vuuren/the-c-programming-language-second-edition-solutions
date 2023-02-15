#include <limits.h>
#include <math.h>
#include <stdio.h>

/* program to determine the ranges of char, short, int and long variables, both
 * signed and unsigned, by printing appropriate values from standard headers and
 * by direct computation. */

int main()
{
    printf("Ranges using values from standard headers:\n");
    printf("\tSigned char range: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("\tUnsigned char range: 0 to %d\n", UCHAR_MAX);

    printf("\tSigned short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("\tUnsigned short range: 0 to %d\n", USHRT_MAX);

    printf("\tSigned int range: %d to %d\n", INT_MIN, INT_MAX);
    printf("\tUnsigned int range: 0 to %u\n", UINT_MAX);

    printf("\tSigned long range: %li to %li\n", LONG_MIN, LONG_MAX);
    printf("\tUnsigned long range: 0 to %lu\n", ULONG_MAX);

    printf("Ranges from direct computation:\n");
    printf("\tUnsigned char range: 0 to %d\n", (unsigned char)(pow(2, CHAR_BIT) - 1));
    char signedchar = (char)(pow(2, CHAR_BIT) - 1);
    printf("\tSigned char range: %d to %d\n", -signedchar - 1, signedchar);

    printf("\tUnsigned short range: 0 to %d\n", (unsigned short)(pow(2, sizeof(short) * CHAR_BIT) - 1));
    short signedshort = (short)(pow(2, sizeof(short) * CHAR_BIT) - 1);
    printf("\tSigned short range: %d to %d\n", -signedshort - 1, signedshort);

    printf("\tUnsigned int range: 0 to %u\n", (unsigned int)(pow(2, sizeof(int) * CHAR_BIT) - 1));
    int signedint = (int)(pow(2, sizeof(int) * CHAR_BIT) - 1);
    printf("\tSigned int range: %d to %d\n", -signedshort - 1, signedshort);

    printf("\tUnsigned long range: 0 to %lu\n", (unsigned long)(pow(2, sizeof(long) * CHAR_BIT) - 1));
    long signedlong = (long)(pow(2, sizeof(long) * CHAR_BIT) - 1);
    printf("\tSigned int range: %li to %li\n", -signedlong - 1, signedlong);
}
