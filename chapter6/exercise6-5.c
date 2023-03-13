#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Write a function undef that will remove a name and definition from the table maintained by lookup and install. */

/* Solution:
 * - Use similar method to lookup function but keep track of previous entry.
 * - If entry is found and there is previous entry, set prev->next to np->next.
 * - Else set the start of the hashtab[hash(name)] to np->next.
 * - Free np's character strings then free the nlist structure
 */

struct nlist
{ /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

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
