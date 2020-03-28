#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define PAGESIZE 4096
#define LOOP 100000

long get_dt(long s1, long u1, long s2, long u2) {
    return (s2-s1)*1e6 + (u2-u1);
}

int main(int argc, char **argv) {
    int pages = atoi(argv[1]);
    int jump = PAGESIZE / sizeof(int);
    struct timeval t;
    
    int *arr = malloc(sizeof(int)*pages*jump);
    for(int i = 0; i< pages*jump; i+=jump)
            arr[i] = 0;

    gettimeofday(&t, NULL);
    long tu = t.tv_usec;
    long ts = t.tv_sec;
    for(int k = 0; k < LOOP; k++)
        for(int i = 0; i< pages*jump; i+=jump)
            arr[i]+=1;
   
    gettimeofday(&t, NULL);
    printf("%lu\n", get_dt(ts, tu, t.tv_sec, t.tv_usec)/pages);
    return 0;
}
