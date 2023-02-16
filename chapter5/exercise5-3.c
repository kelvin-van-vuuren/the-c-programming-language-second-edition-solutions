#include <stdio.h>

/* Write a pointer version of strcat that we showed in Chapter 2: strcat(s, t) copies the string to the end of s. */

/* Original strcat(s, t) from chapter 2:
void strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        ++i;

    while ((s[i++] = t[j++]) != '\0')
        ;
}
*/

void _strcat(char *s, char *t);

void main()
{
    char s[100] = "character pointers";
    char t[] = " and functions";

    _strcat(s, t);
    printf("concatenated result: %s\n", s);
}

/* Pointer version of strcat: concatenate t to the end of s. s must be big enough. */
void _strcat(char *s, char *t)
{
    /* find end of s */
    /* increment of s pointer added to while loop body instead of in loop conditional evaluation because if in loop
     * conditional it would increment when exiting loop which means we would have to decrement s after. Having increment
     * in body saves having to do this extra operation. */
    while (*s)
        s++;

    /* copy t to end of s */
    while ((*s++ = *t++))
        ;
}
