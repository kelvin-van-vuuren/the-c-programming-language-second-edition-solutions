#include <stdio.h>

#define MAX_LEN 1000

/* function escape(s, t) that converts characters like newline and tab into
 * visible escape sequences like \n and \t as it copies the string. Also a
 * function for the other direction, converting escape sequences into the real
 * characters. Both using a switch statement */

void escape(char s[], char v[]);
void unescape(char s[], char v[]);

int main()
{
    char s[] = "Hello\nWorld\t\\";
    char t[MAX_LEN], t2[MAX_LEN];
    
    printf("original string:\n\"%s\"\n", s);
    
    escape(s, t);
    printf("\nescaped:\n\"%s\"\n", t);
    
    unescape(t, t2);
    printf("\nunescaped:\n\"%s\"\n", t2);
}

void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; (t[j] = s[i]) != '\0'; ++i, ++j) {
        switch (t[j]) {
            case '\n':
                t[j++] = '\\';
                t[j] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j] = 't';
                break;
            default:
                t[j] = s[i];
                break;
        }
    }
}
    
void unescape(char s[], char t[])
{
    int i, j;
    
    for (i = 0, j = 0; (t[j] = s[i]) != '\0'; ++i, ++j) {
        if (t[j] == '\\' && s[++i] != '\0') {
            switch (s[i]) {
                case 'n':
                    t[j] = '\n';
                    break;
                case 't':
                    t[j] = '\t';
                    break;
                default:
                    t[++j] = s[i];
                    break;
            } 
        }
    }
}
