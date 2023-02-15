#include <stdio.h>
#include <string.h>

/* Write the function strrindex(s, t), which returns the position of the
 * rightmost occurrence of t in s, or -1 if there is none */

/* This is relatively straightforward change to the original strindex function by searching for the pattern from the end
 * of the string and moving backwards */

#define MAXLINE 1000

int _getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

main()
{
    char line[MAXLINE];
    int found = 0;
    int i;

    while (_getline(line, MAXLINE) > 0)
        if ((i = strrindex(line, pattern)) >= 0) {
            printf("%s\n", line);
            printf("Match occurs at index %d\n", i);
            ++found;
        }
    return found;
}

int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

int strrindex(char s[], char t[])
{
    int i, j, k;
    int len, patternlen;

    len = strlen(s) - 1;
    patternlen = strlen(t) - 1;

    for (i = len - patternlen; i >= 0; --i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }

    return -1;
}
