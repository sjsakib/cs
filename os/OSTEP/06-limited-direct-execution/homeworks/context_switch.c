#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "common.h"

int main(int argc, char **argv) {
    int ITERATION;
    printf("Iteration count: ");
    scanf("%d", &ITERATION);
    int fd1[2];
    int fd2[2];
    char buff[128];

    struct timeval t;

    if(pipe(fd1) < 0) {
        fprintf(stderr, "first pipe failed\n");
    }
    if(pipe(fd2) < 0) {
        fprintf(stderr, "second pipe failed\n");
    }
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        close(fd1[0]);
        close(fd2[1]);

        gettimeofday(&t, NULL);
        int tu = t.tv_usec;
        int ts = t.tv_sec;
        for (int i = 0; i< ITERATION; i++) {
            read(fd2[0], buff, sizeof buff);
            // printf("Read from parent: %s\n\n", buff);

            sprintf(buff, "mommy-%d", i);
            write(fd1[1], buff, strlen(buff));
        }
        gettimeofday(&t, NULL);
        long dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
        printf("In child: %.4f\n", dt/(double)ITERATION);
        
    } else {
        close(fd1[1]);
        close(fd2[0]);
        gettimeofday(&t, NULL);
        int tu = t.tv_usec;
        int ts = t.tv_sec;
        for (int i = 0; i< ITERATION; i++) {
            sprintf(buff, "baby-%d", i);
            write(fd2[1], buff, strlen(buff));
           
            read(fd1[0], buff, sizeof buff);
            // printf("Read from child: %s\n", buff);
        }
        gettimeofday(&t, NULL);
        long dt = get_dt(t.tv_sec, t.tv_usec, ts, tu);
        printf("In parent: %.4f\n", dt/(double)ITERATION);
    }
    return 0;
}