#include <stdio.h>

/* alternate version of squeeze(s1, s2) that deletes each character in s1 that
 * matches any character in the string s2 */

void removechars(char s1[], char s2[]);

void squeeze(char s[], int c);

int main()
{
    char s1[] = "hello";
    char s2[] = "el";

    removechars(s1, s2);
    printf("%s", s1);
}

void removechars(char s1[], char s2[])
{
    int i, j;

    for (i = 0; s1[i] != '\0'; ++i)
        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j])
                squeeze(s1, s1[i--]);
}

void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; ++i)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}
