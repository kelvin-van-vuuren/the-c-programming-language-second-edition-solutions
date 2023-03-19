#include <stdio.h>
#include <stdlib.h>

/* The standard library function calloc(n, size) returns a pointer to n objects of size size, with the storage
 * initialised to zero. Write calloc, by calling malloc or by modifying it. */

/* Solution:
 * - Calculate total space needed by number of objects requested * size of each object.
 * - Request space via call to malloc
 * - Loop through each byte of returned memory using char* and total size to know where to stop, incrementing the char*
 * and setting to zero each time.
 * - Return pointer to start of memory block.
 */

void *_calloc(unsigned n, unsigned size)
{
    int i;
    char *start, *p;
    unsigned total;

    total = n * size;
    start = p = NULL;
    if ((start = malloc(total)))
        for (i = 0, p = start; i < total; ++i)
            *p++ = 0;

    return start;
}
