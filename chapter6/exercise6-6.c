#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on
 * the routines of this section. You may also find getch and ungetch helpful. */

/* Solution:
 * - Use hash table from previous exercise to store definitions from #define's
 * - Use getword function to get words from input. For each word check for #define and #undef else check if needs to be
 * replaced by definition in hash table via lookup.
 * - Used undef function from previous exercise to undefine entries in hashtable when coming across a #undef
 */

int getword(char *word, int lim);

#define MAXWORD 100

struct nlist
{ /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
struct nlist *lookup(char *s);

int handlingmacro = 0; /* used to avoid printing new lines when handling macro */
void handlemacro(char *s); /* handle #define and #undef */

int main()
{
    int n;
    char word[MAXWORD];
    struct nlist *np;

    while (getword(word, MAXWORD) != EOF) {
        if (word[0] == '#') {
            handlemacro(word);
        } else if (isalpha(word[0])) {
            /* check if word needs to be replaced */
            if ((np = lookup(word))) {
                printf("%s", np->defn);
            } else {
                printf("%s", word);
            }
        }
    }
}
/* hash:  form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL; /* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *)np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    struct nlist *np, *prev;
    unsigned hsh;

    hsh = hash(name);
    prev = NULL;
    for (np = hashtab[hsh]; np != NULL; prev = np, np = np->next)
        if (strcmp(name, np->name) == 0)
            break;

    if (np) {
        if (prev)
            prev->next = np->next;
        else
            hashtab[hsh] = np->next;

        free(np->name);
        free(np->defn);
        free(np);
    }
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        if (handlingmacro && c == '\n') {
            handlingmacro = 0;
            break;
        } else if (!handlingmacro) {
            printf("%c", c);
        }
    }

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

void handlemacro(char *s)
{
    char *name, *defn;

    handlingmacro = 1;

    if (getword(s, MAXWORD) != EOF) {
        if (strcmp(s, "define") == 0) {
            /* get name */
            if (isalpha(getword(s, MAXWORD))) {
                name = strdup(s);
                /* get definition */
                if (getword(s, MAXWORD) != EOF) {
                    defn = strdup(s);
                    /* install definition */
                    install(name, defn);
                    free(defn);
                }
                free(name);
            }
        } else if (strcmp(s, "undef") == 0) {
            /* get name then undef */
            getword(s, MAXWORD);
            undef(s);
        }
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
