#include <fcntl.h> /* flags for read and write */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* structure returned by stat */
#include <sys/types.h> /* typedefs */
#include <syscall.h>

/* Modify fsize to print the other information contained in the inode entry */

/* Solution: extended by also printing mode, device, owner group id and inode number of inode. */

int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize:  print the name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("size: %8ld mode: %u device of inode: %lu owner group id: %u inode number: %lu %s\n", stbuf.st_size,
           stbuf.st_mode, stbuf.st_dev, stbuf.st_gid, stbuf.st_ino, name);
}
