#include <stdio.h>

int main(int argc, char** argv) {
    unsigned int c;
    unsigned char s1 = 0, s2 = 0;
    while ((c = getchar()) != EOF) {
        s1 = (s1 + c) % 255;
        s2 = (s1 + s2) % 255;
    }
    printf("Fletcher checksum: (%d, %d)\n", s1, s2);
    return 0;
}
