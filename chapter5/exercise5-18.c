#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Make dcl recover from input errors */

/* solution: check initial datatype being valid */

#define MAXTOKEN 100

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void dcl();
void dirdcl();

int gettoken();
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int etc. */
char out[1000];

#define BUFSIZE 100 /* size of unread character array for ungetch */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch();
void ungetch();

int validdatatype(const char *s);

/* convert declaration to words */
int main()
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        if (tokentype != NAME) {
            printf("%c is not a valid datatype\n", tokentype);
            return 1;
        } else if (!validdatatype(datatype)) {
            printf("%s is not a valid datatype\n", datatype);
            return 1;
        }

        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* return next token */
int gettoken()
{
    int c, getch();
    void ungetch(int);
    char *p = token;

    /* skip blanks and tabs */
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* dcl: parse a declarator */
void dcl()
{
    int ns;

    for (ns = 0; gettoken() == '*';) /* count *'s */
        ++ns;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl()
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) { /* variable name */
        strcat(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            if (tokentype != ']') {
                printf("error: missing ']'\n");
            } else {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of");
            }
        }
    }
}

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}

#define N_DATATYPES 6
const char *datatypes[N_DATATYPES] = {"int", "short", "long", "float", "double", "char"};

int validdatatype(const char *s)
{
    int i;

    for (i = 0; i < N_DATATYPES; ++i)
        if (strcmp(s, datatypes[i]) == 0)
            return 1;

    return 0;
}
