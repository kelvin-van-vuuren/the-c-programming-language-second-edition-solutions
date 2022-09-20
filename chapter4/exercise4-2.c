#include <stdio.h>
#include <ctype.h>

/* extend atof to handle scientific notation of the form 123.45e-6 where a
 * floating point number may be followed by e or E and an optionally signed
 * exponent */

double atof(char s[]);

main()
{
    char s[] = "12.345";
    printf("String '%s' converted to double %f\n", s, atof(s));

    char s2[] = "1.973e-3";
    printf("String '%s' converted to double %f\n", s2, atof(s2));

    char s3[] = "11.973e6";
    printf("String '%s' converted to double %f\n", s3, atof(s3));
    
    char s4[] = "-11.973e6";
    printf("String '%s' converted to double %f\n", s4, atof(s4));
}

double atof(char s[])
{
    double val, power, exppower;
    int i, j, sign, expsign, exp;
    
    for (i = 0; isspace(s[i]); ++i) /* skip whitespace */
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        ++i;

    for (val = 0.; isdigit(s[i]); ++i)
        val = 10. * val + (s[i] - '0');
        
    if (s[i] == '.')
        ++i;

    for (power = 1.; isdigit(s[i]); ++i) {
        val = 10. * val + (s[i] - '0');
        power *= 10.;
    }
    
    power = 1 / power;

    if (s[i] == 'e' || s[i] == 'E') {
        ++i;
        expsign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            ++i;

        for (exp = 0; isdigit(s[i]); ++i)
            exp = 10 * exp + (s[i] - '0');
        
        exppower = 1.;
        for (j = 0; j < exp; ++j)
            exppower *= 10.;
            
        if (expsign == -1)
            exppower = 1 / exppower;

        power *= exppower;
    }

    return sign * val * power;
}
