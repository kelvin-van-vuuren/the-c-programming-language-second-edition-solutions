#include <stdio.h>

/* copy input to output, replacing each tab with \t, each backspace by \b and each backslash by \\ */
int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            putchar(c);
    }
}
