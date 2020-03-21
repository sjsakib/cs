#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>
#include <fcntl.h>
#include "common.h"

int main(int argc, char *argv[]) {
    int ITERATION_COUNT;
    printf("Iteration count: ");
    scanf("%d", &ITERATION_COUNT);
    struct timeval t;
    gettimeofday(&t, NULL);
    long tu = t.tv_usec;
    long ts = t.tv_sec;
    long dt;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        // do nothing
    }
    gettimeofday(&t, NULL);
    dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
    printf("running an empty loop: %.4f\n", dt/(double) ITERATION_COUNT);
    
    gettimeofday(&t, NULL);
    tu = t.tv_usec;
    ts = t.tv_sec;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        gettimeofday(&t, NULL);
    }
    gettimeofday(&t, NULL);
    dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
    printf("getting time: %.4f\n", dt/(double)ITERATION_COUNT);
    
    FILE *fp = fopen("XXX", "w");
    
    gettimeofday(&t, NULL);
    tu = t.tv_usec;
    ts = t.tv_sec;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        fprintf(fp, "");
    }
    gettimeofday(&t, NULL);
    dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
    printf("writting empty string: %.4f\n", dt/(double)ITERATION_COUNT);

    int fd = open("yyy", O_WRONLY);
    char *buff;
    
    gettimeofday(&t, NULL);
    tu = t.tv_usec;
    ts = t.tv_sec;
    for (int i = 0; i<ITERATION_COUNT; i++) {
        write(fd, buff, 0);
    }
    gettimeofday(&t, NULL);
    dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
    printf("writting empty string with `write`: %.4f\n",dt/(double)ITERATION_COUNT);
    return 0;
}
