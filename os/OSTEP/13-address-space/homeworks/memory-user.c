#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Memory amount not provided\n");
        return -1;
    }
    printf("PID: %d\n",(int) getpid());
    int m = atoi(argv[1]);
    int integers = m *((1024*1024) / sizeof(int));
    int *nums = malloc(m * 1024*1024);
    for (int i = 0; i < integers; i++) {
        nums[i]+=1;
    }
    while(1) {
        // nums[i]+=1;
        // i++;
        // if (i == integers) i = 0;
    }
    return 0;
}
