#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCK_SIZE 4096

char buff[BLOCK_SIZE];

char xor(char* block, int len) {
    char sum = 0;
    for(int i = 0; i<len; i++) {
        sum ^= block[i];
    }
    return sum;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Provide checksum file path\n");
        exit(-1);
    }
    int read_count, scan_count, block_count = 0;
    char sum;
    FILE* sumfile = fopen(argv[1], "r");
    
    while ((read_count = read(STDIN_FILENO, buff, BLOCK_SIZE)) > 0) {
        scan_count = fscanf(sumfile, "%c\n", &sum);
        if (scan_count != 1 || sum != xor(buff, read_count)) {
            fprintf(stderr, "Corruption found at block: %d\n", block_count);
            exit(-1);
        }
        block_count++;
    }
    fclose(sumfile);
    printf("No corruption found\n");
    return 0;
}
