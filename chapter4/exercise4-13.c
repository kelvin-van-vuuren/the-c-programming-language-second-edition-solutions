#include <stdio.h>
#include <string.h>

/* Write a recursive version of the function reverse(s), which reverses the string s in place. */

/* Reverse works its way from both ends of the string towards the middle, swapping characters at the two current indexes
 * in each iteration. Because we need to keep track of those indexes, the reverse function had to be implemented using a
 * helper function recursereverse which takes these two indexes as parameters. The function recursereverse calls itself
 * whilst reverse simply starts the call to recursereverse with the first and last index values. */

#define BUFSIZE 100
#define SSIZE 4

void reverse(char s[]);
void recursereverse(char s[], int i, int j);
void swap(char s[], int i, int j);

int main()
{
    char s[] = "reverse this string";
    printf("Recursive reverse of '%s': ", s);
    reverse(s);
    printf("%s\n", s);
}

void reverse(char s[]) { recursereverse(s, 0, strlen(s) - 1); }

void recursereverse(char s[], int i, int j)
{
    swap(s, i, j);
    if (++i < --j)
        recursereverse(s, i, j);
}

void swap(char s[], int i, int j)
{
    char temp;

    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
