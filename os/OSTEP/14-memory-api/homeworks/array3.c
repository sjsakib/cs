#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *x = malloc(10 * sizeof(int));
    free(x + 5);
    return 0;
}
