#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or
 * operand is a separate argument. For example: expr 2 3 4 + * evaluates 2 * (3 + 4). */

/* Solution required taking a slight modification of the polish calculator program from chapter 4 and passing in each
 * argument from the command line to getop instead of reading lines on input. */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#define MAXVAL 100 /* maximum depth of val stack */

#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define MODULUS '%'

int getop(char *s, char *arg);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
void push(double val);
double pop();
void print(); /* print the top element of the stack without popping */

int main(int argc, char *argv[])
{
    int i, type;
    char s[MAXOP];
    double op2;

    while (--argc > 0) {
        type = getop(s, *++argv);
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case ADD:
                push(pop() + pop());
                break;
            case MULTIPLY:
                push(pop() * pop());
                break;
            case SUBTRACT:
                op2 = pop();
                push(pop() - op2);
                break;
            case DIVIDE:
                op2 = pop();
                if (op2 != 0.)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case MODULUS:
                op2 = pop();
                if (op2 != 0.)
                    push((int)pop() % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    printf("result: ");
    print();
}

int getop(char s[], char *arg)
{
    int i, c;

    printf("getop: %s\n", arg);

    /* skip whitespace */
    while ((s[0] = c = *arg++) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    if (c == '-') { /* check if negative number */
        if (!isdigit(c = *arg++)) {
            // --linep;
            return '-';
        }
        s[++i] = c;
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = *arg++))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = *arg++))
            ;

    s[i] = '\0';

    return NUMBER;
}

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can push %g\n", f);
}

double pop()
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.;
    }
}

void print()
{
    if (sp > 0)
        printf("%.8g\n", val[sp - 1]);
    else
        printf("error: can't print top of stack, stack empty\n");
}
