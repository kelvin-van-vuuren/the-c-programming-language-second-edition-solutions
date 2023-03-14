#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

/* Write a private version of scanf analogous to minprintf from the previous section */

/* Solution: similar to previous section except using scanf and extra vars and checks for longs and shorts */

#define MAXCONVSPEC 100 /* max length of conversion specification */

void minscanf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int *ival;
    double *dval;
    unsigned *uval;
    short *shval;
    long *lval;
    unsigned long *ulval;
    unsigned short *ushval;
    int i;
    char convspec[MAXCONVSPEC];

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    i = 0;
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            convspec[i++] = *p;
            continue;
        }

        /* collect any adjustments, field adjustments, paddings, precisions */
        do {
            convspec[i++] = *p++;
        } while (*p && !isalpha(*p));

        /* check if needs to be printed as long or short */
        if (*p == 'h' || *p == 'l' || *p == 'L')
            convspec[i++] = tolower(*p++);

        /* collect format letter */
        convspec[i++] = *p;

        /* end */
        convspec[i] = '\0';

        switch (*p) {
            case 'i': /* fallthrough */
            case 'd':
                if (convspec[i - 2] == 'l') {
                    lval = va_arg(ap, long *);
                    scanf(convspec, lval);
                } else if (convspec[i - 2] == 'h') {
                    shval = va_arg(ap, short *);
                    scanf(convspec, shval);
                } else {
                    ival = va_arg(ap, int *);
                    printf(convspec, ival);
                }
                break;
            case 'o': /* fallthrough */
            case 'x': /* fallthrough */
            case 'X': /* fallthrough */
            case 'u':
                if (convspec[i - 2] == 'l') {
                    ulval = va_arg(ap, unsigned long *);
                    scanf(convspec, ulval);
                } else if (convspec[i - 2] == 'h') {
                    ushval = va_arg(ap, unsigned short *);
                    scanf(convspec, ushval);
                } else {
                    uval = va_arg(ap, unsigned *);
                    printf(convspec, uval);
                }
                uval = va_arg(ap, unsigned *);
                scanf(convspec, uval);
                break;
            case 'e': /* fallthrough */
            case 'E': /* fallthrough */
            case 'g': /* fallthrough */
            case 'G': /* fallthrough */
            case 'f':
                dval = va_arg(ap, double *);
                scanf(convspec, dval);
                break;
            case 'c':
            case 's':
                sval = va_arg(ap, char *);
                scanf(convspec, sval);
                break;
            default:
                scanf(convspec);
                break;
        }
    }
    va_end(ap); /* clean up when its done */
}

int main() {}
