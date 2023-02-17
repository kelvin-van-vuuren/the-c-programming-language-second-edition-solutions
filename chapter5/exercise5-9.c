#include <stdio.h>

/* Rewrite the routines day_of_year and month_day with pointers instead of indexing */

/* Solution replace indexing with pointer arithmentic */

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
int isleap(int year);

int main()
{
    int day, month, year;

    /* check bounds */
    day = 29;
    month = 2;
    year = 2023;
    printf("day_of_year for %d/%d/%d: %d\n", day, month, year, day_of_year(year, month, day));

    year = 2024;
    printf("day_of_year for %d/%d/%d: %d\n", day, month, year, day_of_year(year, month, day));

    month = 13;
    printf("day_of_year for %d/%d/%d: %d\n", day, month, year, day_of_year(year, month, day));

    day = 366;
    printf("month_day for day %d of year %d: ", day, year);
    month_day(year, day, &month, &day);
    printf("month: %d, day: %d\n", month, day);

    day = 366;
    year = 2023;
    printf("month_day for day %d of year %d: ", day, year);
    month_day(year, day, &month, &day);
    printf("month: %d, day: %d\n", month, day);
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (month > 12 || month < 1) {
        printf("day_of_year error: month '%d' out of bounds\n", month);
        return -1;
    }

    leap = isleap(year);

    if (day > *((char *)daytab + 13 * leap + month) || day < 1) {
        printf("day_of_year error: day '%d' out of bounds for month '%d'. This month has %d days.\n", day, month,
               *((char *)daytab + 13 * leap + month));
        return -1;
    }

    for (i = 1; i < month; ++i)
        day += *((char *)daytab + 13 * leap + i);

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = isleap(year);

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        printf("month_day error: day out of bounds\n");
        *pmonth = *pday = -1;
    } else {
        for (i = 1; yearday > *((char *)daytab + 13 * leap + i); ++i)
            yearday -= *((char *)daytab + 13 * leap + i);

        *pmonth = i;
        *pday = yearday;
    }
}

int isleap(int year) { return year % 4 == 0 && year % 100 != 0 || year % 400 == 0; }
