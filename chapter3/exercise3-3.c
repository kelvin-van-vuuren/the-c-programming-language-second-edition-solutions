#include <stdio.h>
#include <string.h>

#define MAXLENGTH 1000

/* function expand(s1, s2) that ezpands shorthand notation like a-z in the
 * string s1 into the equivalent complete list abc...xyz in s2. Allow for letter
 * of either case and digits, and be prepared to handle cases like a-b-c and
 * -a-z. Arrange that a leading or trailing - is taken literally. */

void expand(char s1[], char s2[]);

int main()
{
    //expansion test
    char s1[] = "-a-z random text NOW NUMBERS: 0-9 and 1- test with -caPitals-A-Z consecutive expansions a-z0-9 and a-b-c, a-b-c-z-";
    char s2[MAXLENGTH];
    expand(s1, s2);
    printf("%s\n", s2);
    
    //min tests
    char s1_1[] = "-a-";
    expand(s1_1, s2);
    printf("%s\n", s2);
    
    char s1_2[] = "0-";
    expand(s1_2, s2);
    printf("%s\n", s2);
    
    char s1_3[] = "-a-z";
    expand(s1_3, s2);
    printf("%s\n", s2);
    
    char s1_4[] = "0-5";
    expand(s1_4, s2);
    printf("%s\n", s2);
}

void expand(char s1[], char s2[])
{
    int i, j;
    int prev, current;
    int len, minlen; 

    len = strlen(s1);
    minlen = (s1[0] == '-') ? 4 : 3;
    if (len < minlen) {
        for (i = j = 0; i < len; ++i, ++j)
            s2[j] = s1[i];
    } else {
        for (i = 1, j = 0, prev = s1[0]; (current = s1[i]) != '\0'; ++i, prev = current) {
            if (current == '-') {
                if ((prev >= 'A' && prev <= 'Z' && s1[i + 1] >= prev && s1[i + 1] <= 'Z') 
                    || (prev >= 'a' && prev <= 'z' && s1[i + 1] >= prev && s1[i + 1] <= 'z')
                    || (prev >= '0' && prev <= '9' && s1[i + 1] >= prev && s1[i + 1] <= '9')) {
                    while (++prev < s1[i + 1])
                        s2[j++] = prev;
                    continue;
                }
            }
            s2[j++] = current;
        }
    }
    s2[j++] = '\0';
}
