#include <stdio.h>

/* Define a macro swap(t, x, y) that interchanges two arguments of type t. (Block structure will help) */

#define swap(t, x, y) \
    {                 \
        t temp;       \
                      \
        temp = x;     \
        x = y;        \
        y = temp;     \
    }

int main()
{
    int x, y;

    x = 1;
    y = 2;

    swap(int, x, y);

    printf("x: %d\ny: %d\n", x, y);
}
