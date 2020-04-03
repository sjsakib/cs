#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#define ul unsigned long long

typedef struct {
    int num;
    ul i;
    ul j;
    double long* sum;
} range_t;


float get_dt(struct timeval *t1, struct timeval *t2) {
    return (t2->tv_sec - t1->tv_sec) + (t2->tv_usec - t1->tv_usec) / (float)1e6;
}

long double term(ul i) {
    long double t = ((long double)1.0 / i) * ((long double)1.0 / i);
    return t;
}

void *range(void *arg) {
    range_t *r = (range_t*) arg;
    struct timeval t1;
    gettimeofday(&t1, NULL);
    long double* sum = r->sum;
    for (ul k = r->i; k <= r->j; k++) {
        *sum += term(k);
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    printf("Thread #%d finished in: %fs\n", r->num, get_dt(&t1, &t2));
    return NULL;
}

int main(int argc, char **argv) {
    struct timeval t1;
    gettimeofday(&t1, NULL);

    ul iterations = atoll(argv[1]);
    int number_of_threads = argc >= 3 ? atoi(argv[2]) : 2;
    ul per_thread_iteration = iterations / number_of_threads;

    pthread_t threads[number_of_threads];
    range_t ranges[number_of_threads];
    double long sums[number_of_threads];
    for(int i = 0; i < number_of_threads; i++) {
        ranges[i].i = i*per_thread_iteration + 1;
        ranges[i].j = i == number_of_threads-1 ? iterations : (i+1)*per_thread_iteration;
        ranges[i].num = i;
        sums[i] = 0;
        ranges[i].sum = &sums[i];
        pthread_create(threads + i, NULL, range, ranges + i);
    }
    double long sum = 0;
    for(int i = 0; i< number_of_threads; i++) {
        pthread_join(threads[i], NULL);
        sum += sums[i];
    }

    int precision = log10(iterations) - 1;
    printf("Value of PI %d digits afeter decimal point: %.*Lf\n", precision, precision, sqrtl(sum * (long double)6.0));

    struct timeval t2;
    gettimeofday(&t2, NULL);
    printf("Time: %fs\n", get_dt(&t1, &t2));
    return 0;
}
