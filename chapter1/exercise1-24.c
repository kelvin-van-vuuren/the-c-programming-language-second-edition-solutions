#include <stdio.h>

/* program to check a C program for syntax errors like unbalanced parentheses, brackets and braces */

int main()
{
    int c, quote, escaped;
    int brackets, braces, parentheses;

    brackets = braces = parentheses = 0;
    escaped = 0;

    while (c != EOF && (c = getchar()) != EOF) {
        /* handle comments */
        if (c == '/') {
            if ((c = getchar()) != EOF) {
                if (c == '/') {
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                    continue;
                } else if (c == '*') {
                    while (!((c = getchar() == '*' && (c = getchar()) == '/')) && c != EOF)
                        ;
                    if ((c = getchar()) == '\n')
                        continue;
                }
            }
        }

        /* handle quotes */
        if ((quote = c) == '"' || quote == '\'') {
            while (((c = getchar()) != quote || escaped) && c != EOF)
                escaped = !escaped && c == '\\';
            continue;
        }

        if (c == '[')
            ++brackets;
        else if (c == ']')
            --brackets;
        else if (c == '{')
            ++braces;
        else if (c == '}')
            --braces;
        else if (c == '(')
            ++parentheses;
        else if (c == ')')
            --parentheses;
    }

    if (brackets != 0)
        printf("Syntax Error: unbalanced brackets\n");

    if (braces != 0)
        printf("Syntax Error: unbalanced braces\n");

    if (parentheses != 0)
        printf("Syntax Error: unbalanced parentheses\n");
}
