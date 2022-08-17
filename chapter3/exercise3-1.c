#include <stdio.h>
#include <time.h>

/* write a version of binsearch with only one test inside the loop and measure
 * the difference in run-time */

/* clock timing method taken from
 * https://stackoverflow.com/questions/459691/best-timing-method-in-c */

/* On my Thinkpad X200 with Intel(R) Core(TM)2 Duo CPU P8600 @ 2.40GHz
 * version 1: 315 ms
 * version 2: 326 ms
 * original: 326 ms
 */

#define ARRAY_SIZE 1000000

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int binsearch_original(int x, int v[], int n);

int main()
{
    clock_t start, diff;
    int i, msec;
    int v[ARRAY_SIZE];
    
    for (i = 0; i < ARRAY_SIZE; ++i)
        v[i] = i;

    start = clock();
    for (i = 0; i < ARRAY_SIZE; ++i)
        binsearch(i, v, ARRAY_SIZE);
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Binary search version 1 time taken: %d seconds %d milliseconds\n", msec/1000, msec%1000);
        
    start = clock();
    for (i = 0; i < ARRAY_SIZE; ++i)
        binsearch2(i, v, ARRAY_SIZE);
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Binary search version 2 time taken: %d seconds %d milliseconds\n", msec/1000, msec%1000);
    
    start = clock();
    for (i = 0; i < ARRAY_SIZE; ++i)
        binsearch_original(i, v, ARRAY_SIZE);
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Binary search original version time taken: %d seconds %d milliseconds\n", msec/1000, msec%1000);
}

/* Version 1: keeps looping until low == high. At this point v[mid] will equal x
 * if present in array. */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2; 
        if (x < v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }
    
    return (v[mid] == x) ? mid : -1;
}

/* Version 2: keeps looping unitl low == high or v[mid] == x. I think
 * technically this doesn't count as keeping only one check inside the loop (?)
 * but have added it in for testing purposes anyway */
int binsearch2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2; 
    while (low < high && v[mid] != x) {
        mid = (low + high) / 2; 
        if (x < v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }
    
    return (v[mid] == x) ? mid : -1;
}

/* from book */
int binsearch_original(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2; 
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    
    return -1;
}
