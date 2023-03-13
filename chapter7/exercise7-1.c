#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with,
 * as found in argv[0] */

/* Solution: compare argv[0] to 'lower' or 'upper' and store corresponding case conversion function in pointer then use
 * this function to on each character read from input */

int main(int argc, char *argv[])
{
    int c;
    int (*conversion)(int);

    if (strcmp(argv[0], "lower") == 0) {
        conversion = tolower;
    } else if (strcmp(argv[0], "upper") == 0) {
        conversion = toupper;
    } else {
        printf("error: invoke with name 'upper' or 'lower'\n");
        return 1;
    }

    while ((c = getchar()) != EOF)
        putchar(conversion(c));

    return 0;
}
