#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Specify file/directory\n");
        exit(-1);
    }
    struct stat statbuf;
    if (stat(argv[1], &statbuf) < 0) {
        printf("Failed to get stats\n");
        exit(-1);
    }
    printf("Inode       : %lu\n", statbuf.st_ino);
    printf("Size        : %'ld\n", statbuf.st_size);
    printf("Type        : ");
    switch (statbuf.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    printf("Link count  : %lu\n", statbuf.st_nlink);
    return 0;
}