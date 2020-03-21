#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    struct timeval t;
    gettimeofday(&t, NULL);
    long t1 = t.tv_usec;
    long sum = 0;
    for(int i = 0;i< 100; i++) {
        gettimeofday(&t, NULL);
        sum += t.tv_usec - t1;
        printf("%ld\n", t.tv_usec - t1);
    }
    printf("Average delay %ld\n", sum/100);
}