#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Write a program that reads a C program and prints in alphabetical order each group of variable names that are
 * identical in the first 6 character, but different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line. */

/* Solution: use similar tree implementation from previous section of book to store the names in alphabetical order.
 * Adding node left or right in the tree determined by compare function that checks that two words are identical for the
 * first n characters then different somewhere after. getword function modified slightly to only returns words that are
 * not within strings or comments. */

#define MAXWORD 100

int identical = 6; /* number of characters that must match at start of string */

struct tnode
{
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc();
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int comp(char *s, char *t);

void printtree(struct tnode *node);

enum
{
    STRING,
    SLASHCOMMENT,
    STARCOMMENT,
    PREPROCESSOR,
    NONE
};

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (--argc && isdigit((*++argv)[0]))
        identical = atoi(*argv);

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) > identical)
            root = addtree(root, word);

    printtree(root);
}

struct tnode *addtree(struct tnode *node, char *word)
{
    int cond;

    if (node == NULL) {
        node = talloc();
        node->word = strdup(word);
        node->left = node->right = NULL;
    } else if ((cond = comp(word, node->word)) < 0) {
        node->left = addtree(node->left, word);
    } else if (cond > 0) {
        node->right = addtree(node->right, word);
    }

    return node;
}

/* talloc: make a tnode */
struct tnode *talloc() { return (struct tnode *)malloc(sizeof(struct tnode)); }
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

        /* only want to get words that arent part of string or comment */
        if (wordstate == NONE || wordstate == PREPROCESSOR)
            *w++ = c;
    }

    *w = '\0';
    return word[0];
}

int comp(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; ++i)
        if (s[i] == '\0')
            return 0;

    if (i < identical)
        return 0;

    return s[i] - t[i];
}

void printtree(struct tnode *node)
{
    if (node) {
        printtree(node->left);
        printf("%s\n", node->word);
        printtree(node->right);
    }
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
