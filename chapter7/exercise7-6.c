#include <stdio.h>
#include <string.h>

/* Write a program to compare two files, printing the first line where they differ */

/* Solution:
 * - read in files from command line
 * - Loop through each line of files using reading in using fgets
 * - If one file has not ended before the other, compare strcmp the read lines.
 **/

#define MAXLINE 100

#define NFILES 2

int main(int argc, char *argv[])
{
    FILE *fp[NFILES];
    int i, line;
    char s[MAXLINE], t[MAXLINE];
    char *filename[NFILES];
    char *sp, *tp;

    if (argc != 3) {
        printf("error: input requires two file names\n");
        return 1;
    } else {
        i = 0;
        while (--argc > 0) {
            if ((fp[i] = fopen((filename[i] = *++argv), "r")) == NULL) {
                printf("error: cant't open %s\n", *argv);
                return 1;
            }
            ++i;
        }

        line = 1;
        do {
            sp = fgets(s, MAXLINE, fp[0]);
            tp = fgets(t, MAXLINE, fp[1]);

            if (sp == s && tp == t) {
                if (strcmp(s, t))
                    printf("First difference at line %d\nFile '%s': '%s'\nFile '%s': '%s'\n", line, filename[0], s,
                           filename[1], t);
            } else if (sp != s && tp == t) {
                printf("File '%s' ends before File '%s' at line %d\n", filename[0], filename[1], line);
            } else if (sp == s && tp != t) {
                printf("File '%s' ends before File '%s' at line %d\n", filename[1], filename[0], line);
            }
            ++line;
        } while (sp == s && tp == t);
    }

    return 0;
}
