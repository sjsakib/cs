#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define INDENT 6

char indent[1024];


void join_path(char* path1, char* path2, char* final) {
    sprintf(final, "%s%s%s", path1, path1[strlen(path1)-1] == '/' ? "" : "/", path2);
}

void print_contents(char* path, int level) {
    struct dirent* pDirent;
    DIR *pDir;
    struct stat statbuf;
    char new_path[1024];
    
    if ((pDir = opendir(path)) == NULL) {
        return;
    }
    while ((pDirent = readdir(pDir)) != NULL ) {
        if (!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, "..")) {
            continue;
        }
       
        printf("%s", indent);
        
        printf("%s\n", pDirent->d_name);
        join_path(path, pDirent->d_name, new_path);
        if (stat(new_path, &statbuf) < 0) {
            continue;
        }
        if (S_ISDIR(statbuf.st_mode)) {
            sprintf(indent+(level*INDENT), "\u2502   \u251c\u2500");
            print_contents(new_path, level+1);
            sprintf(indent+(level*INDENT), "\u251c\u2500");
        }
    }
}


int main(int argc, char** argv) {
    char* dir = argc >= 2 ? argv[1] : ".";
    sprintf(indent, "\u251c\u2500");
    print_contents(dir, 0);
    return 0;
}
