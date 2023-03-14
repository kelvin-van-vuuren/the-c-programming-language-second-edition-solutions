#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

/* Revise minprintf to handle more of the other facilities of printf. */

/* Solution: collect conversion specification from fmt character string, then add cases for  all format characters
 * listed in table 7.1 from the book */

#define MAXCONVSPEC 100 /* max length of conversion specification */

void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    unsigned uval;
    long lval;
    int i;
    char convspec[MAXCONVSPEC];

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        /* collect any adjustments, field adjustments, paddings, precisions */
        i = 0;
        do {
            convspec[i++] = *p++;
        } while (*p && !isalpha(*p));

        /* check if needs to be printed as long or short */
        if (*p == 'h' || *p == 'l')
            convspec[i++] = *p++;

        /* collect format letter */
        convspec[i++] = *p;

        /* end */
        convspec[i] = '\0';

        switch (*p) {
            case 'i': /* fallthrough */
            case 'c': /* fallthrough */
            case 'd':
                if (convspec[i - 2] == 'l') {
                    lval = va_arg(ap, long);
                    printf(convspec, lval);
                } else {
                    ival = va_arg(ap, int);
                    printf(convspec, ival);
                }
                break;
            case 'o': /* fallthrough */
            case 'x': /* fallthrough */
            case 'X': /* fallthrough */
            case 'u':
                uval = va_arg(ap, unsigned);
                printf(convspec, uval);
                break;
            case 'e': /* fallthrough */
            case 'E': /* fallthrough */
            case 'g': /* fallthrough */
            case 'G': /* fallthrough */
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf(convspec, sval);
                break;
            default:
                printf(convspec);
                break;
        }
    }
    va_end(ap); /* clean up when its done */
}

int main() {}
