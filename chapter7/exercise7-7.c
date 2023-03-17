#include <stdio.h>
#include <string.h>

/* Modify the pattern finding program of chapter 5 to take its input from a set of named files or, if no files are named
 * as arguments, from the standard input. Should the file name be printed when a matching line is found? */

/* Solution:
 * - create file pointers from command line args or set to stdin if none
 * - copy pattern from command line arg removing start / end quotes if exists
 * - loop through files getting each line and comparing to pattern. Similar to original except using fgets instead of
 * getline
 *
 * Print filename when matching line is found so that matches in different files can be distinguished
 * */
#define MAXLINE 1000

#define MAXFILES 100

void getpattern(char *from, char *to);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    long lineno;
    int i, nfiles;
    int c, except, number, found;
    char pattern[MAXLINE];
    FILE *fp[MAXFILES];
    char *filename[MAXFILES];
    char s[MAXLINE];
    char *sp;

    lineno = except = number = found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    fprintf(stderr, "find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }

    /* copy pattern from cmd line arg into pattern var, removing beginning and end quotations */
    if (argc-- > 0)
        getpattern(*argv++, pattern);

    nfiles = 0;
    if (argc >= 1) {
        do {
            if ((fp[nfiles] = fopen((filename[nfiles] = *argv++), "r")) == NULL) {
                fprintf(stderr, "error: cant't open %s\n", filename[nfiles]);
                return 1;
            }
            ++nfiles;
        } while (--argc > 0);
    } else {
        *fp = stdin;
        *filename = "stdin";
        ++nfiles;
    }

    if (argc != 0) {
        printf("Usage: find -x -n pattern <files>\n");
    } else {
        for (i = 0; i < nfiles; ++i) {
            do {
                sp = fgets(s, MAXLINE, fp[i]);
                if (sp == s) {
                    if ((strstr(s, pattern) != NULL) != except) {
                        printf("%s: ", filename[i]);
                        if (number)
                            printf("%ld: ", lineno);
                        printf("%s", s);
                        ++found;
                    }
                }
            } while (sp == s);
        }
    }
    return found;
}

void getpattern(char *from, char *to)
{
    if (*from != '"')
        *to++ = *from;

    while ((*to++ = *++from))
        ;

    if (*(to - 2) == '"')
        *(to - 2) = '\0';
}
