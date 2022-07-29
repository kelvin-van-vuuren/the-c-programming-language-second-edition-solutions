#include <stdio.h>
#define MAXLINE 1000 /* maximum line length */

int _getline(char line[], int maxline);
void reverse(char line[], int len);

/* program to reverse its input a line at a time */

int main()
{
    int len;                /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s", line);
    }
}

int _getline(char line[], int maxline)
{
    int c, i;

    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

void reverse(char line[], int len)
{
    int i, j, temp;
    
    if (len > 2) {
        for (i = 0, j = len - 2; i <= j; ++i, --j) {
            temp = line[i]; 
            line[i] = line[j];  
            line[j] = temp;
        }
    }
}
