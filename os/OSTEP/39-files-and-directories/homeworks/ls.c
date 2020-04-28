#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


void join_path(char* path1, char* path2, char* final) {
    sprintf(final, "%s%s%s", path1, path1[strlen(path1)-1] == '/' ? "" : "/", path2);
}

void print_stats(char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) < 0) {
        printf("Failed to get stats\n");
        exit(-1);
    }
    printf("%5u %5u %5lu %12ld   ", statbuf.st_uid, statbuf.st_uid, statbuf.st_nlink, statbuf.st_size);
    if (S_ISDIR(statbuf.st_mode)) printf("📂 ");
    else if (S_ISREG(statbuf.st_mode)) printf("📄 ");
    else if (S_ISLNK(statbuf.st_mode)) printf("🔗 ");
    else printf("👽 ");
}


int main(int argc, char** argv) {
    int show_details = 0, opt;
    while ((opt = getopt(argc, argv, "l")) != -1) {
        if (opt == 'l') show_details = 1;
    }
    char* dir = optind < argc ? argv[optind] : ".";
    
    char path[1024];
    struct dirent* pDirent;
    DIR *pDir;
    
    if ((pDir = opendir(dir)) == NULL) {
        fprintf(stderr, "Failed to open directory\n");
        exit(-1);
    }
    if (show_details) {
        printf("  UID   GID NLink         Size Type Name\n");
    }
    while ((pDirent = readdir(pDir)) != NULL ) {
        if (show_details) {
            join_path(dir, pDirent->d_name, path);
            print_stats(path);
        }
        printf("%s\n", pDirent->d_name);
    }
    return 0;
}