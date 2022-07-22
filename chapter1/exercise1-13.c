#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

#define MAX_LENGTH 20 /* max word length */

/* program to print a hisogram of the lengths of words in its input */
/* Note: this program will count symbols and digits as part of words */

int main()
{
    int c, i, j, wlength, state;
    int lengths[MAX_LENGTH + 1];
    
    for (i = 0; i < MAX_LENGTH; ++i)
        lengths[i] = 0;
    
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                ++lengths[wlength - 1];
                wlength = 0;
                state = OUT;
            }
        } else {
            if (wlength < MAX_LENGTH)
                ++wlength;
            state = IN;
        }
    }
    
    printf("Horizontal Histogram:\n");
    printf(" length | occurences\n");
    for (i = 0; i < MAX_LENGTH; ++i) {
        printf("     %2d | ", i + 1);
        for (j = 0; j < lengths[i]; ++j)
            putchar('+');
        putchar('\n');
    }
    
    putchar('\n');
        
    printf("Vertical Histogram:\n");
    int max = 0;
    for (i = 0; i < MAX_LENGTH; ++i)
        if (lengths[i] > max)
            max = lengths[i];
            
    for (i = max; i > 0; --i) {
        printf("    %2d | ", i);
        for (j = 0; j < MAX_LENGTH; ++j)
            printf("%3c", lengths[j] >= i ? '+' : ' ');
        putchar('\n');
    }
    
    printf("         ");
    for (i = 0; i < MAX_LENGTH; ++i)
        printf("___");
        
    putchar('\n');
        
    printf("         ");
    for (i = 0; i < MAX_LENGTH; ++i)
        printf("%3d", i + 1);
}
