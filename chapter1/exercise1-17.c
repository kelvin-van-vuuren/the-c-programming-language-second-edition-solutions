#include <stdio.h>
#define MAXLINE 1000    /* maximum line length */
#define MINLENGTH 80    /* minimum length of lines to be printed */

int _getline(char line[], int maxline);

/* print all input lines that are longer than 80 characters */

int main()
{
    int len;                /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0)
        if (len > MINLENGTH)
            printf("%s", line);
}

int _getline(char line[], int maxline)
{
    int c, i, length;

    for(i = 0, length = 0; (c = getchar()) != EOF && c != '\n'; ++length)
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

