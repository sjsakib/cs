#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *x = malloc(10 * sizeof(int));
    x[10] = 0;
    return 0;
}
