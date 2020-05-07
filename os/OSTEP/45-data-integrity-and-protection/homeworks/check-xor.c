#include <stdio.h>

int main(int argc, char** argv) {
    unsigned int c;
    unsigned char sum = 0;
    while ((c = getchar()) != EOF) {
        sum^=c;
    }
    printf("XOR Checksum: %d\n", sum);
    return 0;
}
