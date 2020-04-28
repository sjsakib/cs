#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BLOCKSIZE 5
#define MAX_SIZE 1<<20

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void reverse(char* s, int len) {
    char tmp;
    for(int i = 0; i < len / 2; i++) {
        tmp = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = tmp;
    }
}

int main(int argc, char** argv) {
    int lines = 1, opt;
    char* path;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        if (opt == 'n') lines = atoi(optarg);
    }
    if (optind >= argc) {
        fprintf(stderr, "File path is required\n");
        exit(-1);
    } else {
        path = argv[optind];
    }

    int fd;
    struct stat statbuf;
    if ((fd = open(path, O_RDONLY)) < 0) {
        fprintf(stderr, "Can't read file %s\n", path);
    }
    fstat(fd, &statbuf);

    int done = 0, seek_pos = BLOCKSIZE, pos = 0, len, res_pos = 0, read_size;
    char buff[BLOCKSIZE+1], res[MAX_SIZE];
    while (done < lines) {
        lseek(fd, MAX(-statbuf.st_size, -seek_pos), SEEK_END);
        read_size = MIN(BLOCKSIZE, statbuf.st_size - pos);
        read(fd, buff, read_size);
        len = strlen(buff);
        len = MIN(len, read_size);
        pos+= read_size;
        for(int i = len-1; i >= 0; i--) {
            if (buff[i] == '\n' && res_pos != 0) done++;
            if (done >= lines) break;
            res[res_pos++] = buff[i];
        }
        if (len < BLOCKSIZE) break;
        seek_pos += BLOCKSIZE;
    }
    res[res_pos] = '\0';
    reverse(res, res_pos);
    printf("%s\n", res);
    return 0;
}