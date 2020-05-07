#include <stdio.h>

#define POLY 0x1021

int main(int argc, char** argv) {
    unsigned short crc = 0, first_bit;
    int ch;

    while ((ch = getchar()) != EOF) {
        for (int i = 0; i < 8; i++) {
            first_bit = crc >> 15;

            crc <<= 1;
            if (ch & 1 << i) {
                crc+=1;
            }

            if (first_bit) {
                crc ^= POLY;
            }
        }
    }
    
    for (int i = 0; i < 16; i++) {
        first_bit = crc >> 15;
        crc <<= 1;
        if (first_bit) {
            crc ^= POLY;
        }
    }
    printf("CRC: 0x%x\n", crc);
    return 0;
}
