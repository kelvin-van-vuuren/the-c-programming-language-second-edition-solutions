#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* An alternate organisation uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise
 * the calculator to use this approach. */

/* Implemented by using global buffer for input lines to be read into and a global variable for keeping track of the
current read position in the buffer. Calls to getch and ungetch were replaced with incrementing and decrementing the
line buffer position variable. */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#define MAXVAL 100 /* maximum depth of val stack */

#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define MODULUS '%'

#define PRINT '!'
#define DUPLICATE '#'
#define SWAP '$'
#define CLEAR '&'
#define SIN '~'
#define EXP '_'
#define POW '^'

#define SETVAR '(' /* lower case to set variable */
#define GETVAR ')' /* upper case to get variable (push onto stack) */

#define VARSIZE 26
double vars[VARSIZE];

int getop(char s[]);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
void push(double val);
double pop();
void print(); /* print the top element of the stack without popping */
void duplicate(); /* print the top element of the stack without popping */
void swap(); /* swap the top two elements of stack */
void clear();

#define MAXLINE 100
char line[MAXLINE]; /* buffer for reading in lines of input */
int linep = 0; /* current position in line */
int _getline(char line[], int max);

/* reverse Polish calculator */
main()
{
    int i, type;
    double op2;
    char s[MAXOP];

    for (i = 0; i < VARSIZE; ++i)
        vars[i] = 0;

    while (_getline(line, MAXLINE)) {
        linep = 0;
        while (line[linep] != '\0') {
            while ((type = getop(s)) != '\0') {
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
                    case PRINT:
                        print();
                        break;
                    case DUPLICATE:
                        duplicate();
                        break;
                    case SWAP:
                        swap();
                        break;
                    case CLEAR:
                        clear();
                        break;
                    case SIN:
                        push(sin(pop()));
                        break;
                    case EXP:
                        push(exp(pop()));
                        break;
                    case POW:
                        op2 = pop();
                        push(pow(pop(), op2));
                        break;
                    case SETVAR:
                        vars[(int)s[0] - 'a'] = pop();
                        break;
                    case GETVAR:
                        push(vars[(int)s[0] - 'A']);
                        break;
                    case '\n':
                        printf("\t%.8g\n", pop());
                        break;
                    default:
                        printf("error: unknown command %s\n", s);
                        break;
                }
            }
        }
    }
}

int getop(char s[])
{
    int i, c;

    /* skip whitespace */
    while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (isalpha(s[0]))
        return (islower(s[0])) ? SETVAR : GETVAR;

    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    if (c == '-') { /* check if negative number */
        if (!isdigit(c = line[linep++])) {
            --linep;
            return '-';
        }
        s[++i] = c;
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[linep++]))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[linep++]))
            ;

    s[i] = '\0';
    if (c != EOF)
        --linep;

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
        printf("Top element of stack: %.8g\n", val[sp - 1]);
    else
        printf("error: can't print top of stack, stack empty\n");
}

void duplicate()
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("error: cannot duplicate top element, stack empty\n");
}

void swap()
{
    int temp;

    if (sp > 1) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("error: stack size is %d, cannot swap two elements\n", sp);
    }
}

void clear() { sp = 0; }

int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}
