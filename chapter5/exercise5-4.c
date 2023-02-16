#include <stdio.h>
#include <string.h>

/* Write the function strend(s, t), which returns 1 if the string t occurs at the end of the string s, and zero
 * otherwise. */

#define LEN 4

int strend(char *s, char *t);

int main()
{
    int i;
    char *s[LEN] = {"test string", "string", "nice", "nice one"};
    char *t[LEN] = {"string", "string", "one", "one"};

    for (i = 0; i < LEN; ++i)
        printf("String '%s' appear at the end of string '%s': %d\n", t[i], s[i], strend(s[i], t[i]));
}

int strend(char *s, char *t)
{
    int tlen, slen;

    slen = strlen(s);
    tlen = strlen(t);

    if (tlen <= slen)
        for (s += slen - tlen; *s == *t; ++s, ++t)
            if (*s == '\0')
                return 1;

    return 0;
}
