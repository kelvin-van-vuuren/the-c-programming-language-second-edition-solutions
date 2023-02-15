#include <assert.h>
#include <stdio.h>

int main()
{
    int c;

    c = getchar() != EOF;
    printf("%d", c);
    assert(c == 1 || c == 0);
}
