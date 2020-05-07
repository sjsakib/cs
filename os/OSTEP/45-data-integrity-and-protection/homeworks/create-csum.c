#include <stdio.h>
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
        fprintf(stderr, "Provide output file path\n");
    }
    int read_count;
    FILE* output = fopen(argv[1], "w");
    while ((read_count = read(STDIN_FILENO, buff, BLOCK_SIZE)) > 0) {
        fprintf(output, "%c\n", xor(buff, read_count));
    }
    fclose(output);
    return 0;
}
