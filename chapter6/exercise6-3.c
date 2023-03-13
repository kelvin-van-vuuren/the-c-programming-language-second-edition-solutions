#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Write a cross-referenceer that prints a list of all words in a document, and for each, a list of the line numbers on
 * which it occurs. Remove noise words like 'the', 'and', and so on. */

/* Solution:
 * - Store each unique word in a node in binary tree like in previous exercises.
 * - Before storing word in binary tree, check that it is not in noise word array.
 * - Use a linked list at each node to store list of line numbers the word appears at.
 * - Keep track of line number via occurrences of '\n'. Requires modification of getword to return new lines.
 */

#define MAXWORD 100

struct linkedlist
{
    int linenumber;
    struct linkedlist *next;
};

struct tnode
{
    char *word;
    struct linkedlist *linenumbers;
    struct tnode *right;
    struct tnode *left;
};

#define NNOISE 2
char *noise[NNOISE] = {"the", "and"}; /* noise words to not include */
int isnoise(char *s);

struct tnode *talloc();
struct linkedlist *lalloc();
struct tnode *addtree(struct tnode *, char *, int linenumber);
void addlinenumber(struct tnode *node, int linenumber);
void treeprint(struct tnode *);
int getword(char *, int);

void printtree(struct tnode *node);
void printlinenumbers(struct tnode *node);

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    int linenumber;

    linenumber = 1;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, linenumber);
        else if (word[0] == '\n')
            ++linenumber;
    }

    printtree(root);
}

int isnoise(char *s)
{
    int i;

    for (i = 0; i < NNOISE; ++i)
        if (strcmp(noise[i], s) == 0)
            return 1;

    return 0;
}

struct tnode *addtree(struct tnode *node, char *word, int linenumber)
{
    int cond;

    if (node == NULL) {
        node = talloc();
        node->word = strdup(word);
        node->linenumbers = lalloc();
        node->linenumbers->linenumber = linenumber;
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0) {
        addlinenumber(node, linenumber);
    } else if (cond > 0) {
        node->right = addtree(node->right, word, linenumber);
    } else {
        node->left = addtree(node->left, word, linenumber);
    }

    return node;
}

/* talloc: make a tnode */
struct tnode *talloc() { return (struct tnode *)malloc(sizeof(struct tnode)); }

struct linkedlist *lalloc() { return (struct linkedlist *)malloc(sizeof(struct linkedlist)); }

void addlinenumber(struct tnode *node, int linenumber)
{
    struct linkedlist *curr;

    for (curr = node->linenumbers; curr->next != NULL; curr = curr->next)
        ;

    curr->next = lalloc();
    curr->next->linenumber = linenumber;
    curr->next->next = NULL;
}
/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            break;

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
}

void printtree(struct tnode *node)
{
    if (node) {
        printtree(node->left);
        printf("%s\n", node->word);
        printlinenumbers(node);
        printtree(node->right);
    }
}

void printlinenumbers(struct tnode *node)
{
    struct linkedlist *curr;

    for (curr = node->linenumbers; curr != NULL; curr = curr->next)
        printf("%d,", curr->linenumber);

    printf("\n");
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
