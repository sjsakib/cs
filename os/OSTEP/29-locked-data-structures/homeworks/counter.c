#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <locale.h>

#include "common.h"


typedef struct {
    long counter;
    pthread_mutex_t lock;
} counter_t;

typedef struct {
    counter_t * counter;
    int iterations;
    int i;
} arg_t;

void init_counter(counter_t* counter) {
    counter->counter = 0;
    pthread_mutex_init(&counter->lock, NULL);
}

void inc_counter(counter_t* counter) {
    pthread_mutex_lock(&counter->lock);
    counter->counter+=1;
    pthread_mutex_unlock(&counter->lock);
}

int get_count(counter_t* counter) {
    int ret = -1;
    pthread_mutex_lock(&counter->lock);
    ret = counter->counter;
    pthread_mutex_unlock(&counter->lock);
    return ret;
}

void* inc(void* args) {
    arg_t* arg = (arg_t*) args;
    struct timeval t1;
    gettimeofday(&t1, NULL);
    for(int i = 0;i<arg->iterations; i++) {
        inc_counter(arg->counter);
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    printf("Thread #%d: %f\n", arg->i, get_dt(&t1, &t2));
    return NULL;
}

int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    int number_of_threads = atoi(argv[1]);
    int iterations = atoi(argv[2]);

    counter_t counter;
    init_counter(&counter);

    pthread_t threads[number_of_threads];
    arg_t args[number_of_threads];

    for(int i = 0; i< number_of_threads; i++) {
        args[i].counter = &counter;
        args[i].iterations = iterations / number_of_threads;
        args[i].i = i;
        pthread_create(&threads[i], NULL, inc, &args[i]);
    }

    struct timeval t1;
    gettimeofday(&t1, NULL);
    for(int i = 0; i<number_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    printf("\nPer thread iterations: %'d\n", iterations/number_of_threads);
    printf("Total time: %f\n", get_dt(&t1, &t2));
    return 0;
}
