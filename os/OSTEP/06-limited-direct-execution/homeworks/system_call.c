#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <fcntl.h>


#define ITERATION_COUNT 100000

int main(int argc, char *argv[]) {
    struct timeval t;
    gettimeofday(&t, NULL);
    long tu = t.tv_usec;
    long ts = t.tv_sec;
    long sum = 0;
    long dt;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        // do nothing
    }
    gettimeofday(&t, NULL);
    dt = t.tv_usec - tu;
    assert(ts == t.tv_sec);
    printf("running an empty loop: %.4f\n", dt/(double) ITERATION_COUNT);
    
    sum = 0;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        gettimeofday(&t, NULL);
        sum += t.tv_usec - tu;
        tu = t.tv_usec;
    }
    printf("getting time: %.4f\n", sum/(double)ITERATION_COUNT);
    
    FILE *fp = fopen("XXX", "w");
    
    tu = t.tv_usec;
    ts = t.tv_sec;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        fprintf(fp, "");
    }
    gettimeofday(&t, NULL);
    dt = t.tv_usec - tu;
    assert(ts == t.tv_sec);
    printf("writting empty string: %.4f\n", dt/(double)ITERATION_COUNT);

    int fd = open("yyy", O_WRONLY);
    char *buff;
    
    tu = t.tv_usec;
    ts = t.tv_sec;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        write(fd, buff, 0);
    }
    gettimeofday(&t, NULL);
    dt = t.tv_usec - tu;
    assert(ts == t.tv_sec);
    printf("writting empty string with `write`: %.4f\n",dt/(double)ITERATION_COUNT);
    return 0;
}
