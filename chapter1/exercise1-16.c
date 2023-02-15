#include <stdio.h>
#define MAXLINE 1000 /* maximum line length */

int _getline(char line[], int maxline);
void copy(char to[], char from[], int maxline);

/* print length of longest input line and its text up to the limit defined by MAXLINE */

int main()
{
    int len; /* current line length */
    int max; /* maximum length seen so far */
    char line[MAXLINE]; /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = _getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line, MAXLINE);
        }
    }

    if (max > 0)
        printf("%d %s", max, longest);
}

int _getline(char line[], int maxline)
{
    int c, i, length;

    for (i = 0, length = 0; (c = getchar()) != EOF && c != '\n'; ++length)
        if (i < maxline - 1)
            line[i++] = c;

    if (c == '\n') {
        ++length;
        if (i < maxline - 1)
            line[i++] = c;
    }

    line[i] = '\0';

    return length;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[], int maxline)
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
