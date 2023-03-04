#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Write a version of getword which handles underscores, string constants, comments, or preprocessor control lines */

/* Solution: have made the assumption that keywords contained within string constants, comments or preprocessor
 * statements are not being counted by the program. Therefore, getword will return entire string constant / comment /
 * preprocessor statement as a single word. */

#define MAXWORD 100

struct key
{
    char *word;
    int count;
} keytab[] = {"auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0, "default", 0,
              /* ... */
              "unsigned", 0, "void", 0, "volatile", 0, "while", 0};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

enum
{
    STRING,
    SLASHCOMMENT,
    STARCOMMENT,
    PREPROCESSOR,
    NONE
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, prev, wordstate, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    wordstate = NONE;
    if (c == '"') {
        wordstate = STRING;
    } else if (c == '/') {
        if ((c = getch()) == '*') {
            wordstate = STARCOMMENT;
        } else if (c == '/') {
            wordstate = SLASHCOMMENT;
        }
    } else if (c == '#') {
        wordstate = PREPROCESSOR;
    } else if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    while (--lim > 0) {
        prev = c;
        c = getch();

        /* check for end of string */
        if (c == '"') {
            if (wordstate == STRING) {
                if (prev != '\\')
                    break;
            }
        }

        /*check for end of start comment */
        if (c == '/' && prev == '*')
            break;

        /* check for end of string, slash comment and preprocessor directive via newline */
        if (c == '\n') {
            if ((wordstate == SLASHCOMMENT || wordstate == STRING || wordstate == PREPROCESSOR) && prev != '\\')
                break;
        }

        if (wordstate == NONE) {
            if (!isalnum(c) && c != '_') {
                ungetch(c);
                break;
            }
        }

        *w++ = c;
    }

    *w = '\0';
    return word[0];
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

#define BUFSIZE 100 /* size of unread character array for ungetch */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
