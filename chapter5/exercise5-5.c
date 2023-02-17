#include <stdio.h>

/* Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n
 * characters of their arguments strings. For example, strncpy(s, t, n) copies at most n characters of t to s. */

/* Solution used same implementation of non n version of functions with the addition of decrementing the n parameter
 * each loop iteration and stopping when n reached 0. */

void _strncpy(char *s, char *t, int n);
void _strncat(char *s, char *t, int n);
int _strncmp(char *s, char *t, int n);

#define MAXLEN 100

#define N 4

int main()
{
    int n;
    char s[MAXLEN] = "string s";
    char t[] = "string t";
    char u[MAXLEN] = "another ssssssssstring!";

    n = 3;
    printf("strncmp: first %d characters of strings '%s' and '%s': %d\n", n, s, t, _strncmp(s, t, n));
    n = 8;
    printf("strncmp: first %d characters of strings '%s' and '%s': %d\n", n, s, t, _strncmp(s, t, n));
    n = 8;
    printf("strncmp: first %d characters of strings '%s' and '%s': %d\n", n, t, s, _strncmp(t, s, n));
    n = 1;
    printf("strncmp: first %d characters of strings '%s' and '%s': %d\n", n, s, t, _strncmp(s, t, n));
    n = 7;
    printf("strncmp: first %d characters of strings '%s' and '%s': %d\n", n, t, s, _strncmp(t, s, n));

    n = 8;
    printf("strncpy: copy first %d characters of string '%s' to string %s: ", n, t, s);
    _strncpy(s, t, n);
    printf("'%s'\n", s);

    printf("strncat: append first %d characters of string '%s' to string '%s': ", n, t, u);
    _strncat(u, t, n);
    printf("'%s'\n", u);
}

/* copy n characters from t into s */
void _strncpy(char *s, char *t, int n)
{
    while (n-- && (*s++ = *t++))
        ;
}

/* append n characters from t to s */
void _strncat(char *s, char *t, int n)
{
    /* find end of s */
    while (*s)
        s++;

    /* copy t to end of s */
    while (n-- && (*s++ = *t++))
        ;
}

/* compare at the most the first n characters of s and t. Return < 0 if s < t, 0 if s == t, > 0 if s > t */
int _strncmp(char *s, char *t, int n)
{
    for (; --n && *s == *t; ++s, ++t)
        if (*s == '\0')
            return 0;

    return *s - *t;
}
