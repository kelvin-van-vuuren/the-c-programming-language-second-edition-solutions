#include <stdio.h>

int main()
{
    float fahr, celsius;
    int lower, upper, step;
    
    lower = 0;
    upper = 300;
    step = 20;

    printf("Celsius  Fahrenheit\n");
    
    celsius = lower;
    while (celsius <= upper) {
        //celsius = (5.0 / 9.0) * (fahr - 32.0);
        fahr = (celsius * 9.0) / 5.0 - 32.0;
        printf("%7.0f %11.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
