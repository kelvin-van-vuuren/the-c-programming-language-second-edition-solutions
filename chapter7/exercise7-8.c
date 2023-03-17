#include <stdio.h>

/* Write a program to print a set of files, starting each new one on a new page, with a title and a running page count
 * for each file */

/* Solution:
 * - Loop through each command line arg taking as filename to open.
 * - Print title as filename and page count to stdout
 * - Go through each line of file and print to stdout
 */

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *fp;
    int pagecount;
    char s[MAXLINE], *sp;

    pagecount = 0;
    while (--argc > 0) {
        if (!(fp = fopen(*++argv, "r"))) {
            fprintf(stderr, "error: can't open file '%s'", *argv);
        } else {
            /* print title */
            fprintf(stdout, "--- Start of page ---\n");
            fprintf(stdout, "Page Count: %d\nTitle: %s\n\n", ++pagecount, *argv);
            /* print file */
            while ((sp = fgets(s, MAXLINE, fp)) == s)
                fprintf(stdout, "%s", s);

            fprintf(stdout, "--- End of page ---\n\n");
        }
    }
}
