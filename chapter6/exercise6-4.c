#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence.
 * Preced each word by its count. */

/* Solution:
 * - Store each unique word in a node in binary tree like in previous exercises.
 * - Store pointers to tree nodes in an array, then sort this array using qsort library function (similar exercises in
 * chapter 5).
 * - Print list.
 */

#define MAXWORD 100

struct tnode
{
    char *word;
    int count;
    struct tnode *right;
    struct tnode *left;
};

struct tnode *talloc();
struct tnode *addtree(struct tnode *, char *, int linenumber);
int getword(char *, int);

#define MAXDISTINCTWORDS 100
struct tnode *list[MAXDISTINCTWORDS];
int lpos = 0;
void getlist(struct tnode *node);
void printlist();
int numcmp(const void *s1, const void *s2);

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    int linenumber;

    linenumber = 1;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            root = addtree(root, word, linenumber);
        else if (word[0] == '\n')
            ++linenumber;
    }

    getlist(root);
    qsort((void **)list, lpos, sizeof(list[0]), numcmp);
    printlist();
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

struct tnode *addtree(struct tnode *node, char *word, int linenumber)
{
    int cond;

    if (node == NULL) {
        node = talloc();
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0) {
        node->count++;
    } else if (cond > 0) {
        node->right = addtree(node->right, word, linenumber);
    } else {
        node->left = addtree(node->left, word, linenumber);
    }

    return node;
}

/* talloc: make a tnode */
struct tnode *talloc() { return (struct tnode *)malloc(sizeof(struct tnode)); }

void getlist(struct tnode *node)
{
    if (node) {
        getlist(node->left);
        if (lpos < MAXDISTINCTWORDS)
            list[lpos++] = node;
        getlist(node->right);
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const void *s1, const void *s2)
{
    struct tnode **v1, **v2;

    v1 = (struct tnode **)s1;
    v2 = (struct tnode **)s2;

    return (*v2)->count - (*v1)->count;
}

void printlist()
{
    int i;

    for (i = 0; i < lpos; ++i)
        printf("%s, %d\n", list[i]->word, list[i]->count);
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
