#include <stdio.h>
#define MAXLINE 6 /* maximum line length */

int _getline(char line[], int maxline);
int remove_trailing_whitespace(char line[], int len);

/* program to remove trailing blanks and tabs from each line of input and to delete entirely blank lines */

int main()
{
    int len; /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0) {
        len = remove_trailing_whitespace(line, len);
        if (line[0] != '\0') {
            printf("%s", line);
            if (len > 1 && line[len - 2] != '\n')
                printf("\n");
        }
    }
}

int _getline(char line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i] = c;

    if (c != EOF)
        line[++i] = '\0';

    return i;
}

int remove_trailing_whitespace(char line[], int len)
{
    int i;

    for (i = len - 2; i >= 0 && (line[i] == ' ' || line[i] == '\t'); --i)
        ;

    line[++i] = '\0';

    return ++i;
}
