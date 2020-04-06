#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <locale.h>

#include "common.h"

#define NUMCPUS 12

int THREADS[NUMCPUS];

typedef struct {
    long count;
    long locals[NUMCPUS];
    pthread_mutex_t glock;
    pthread_mutex_t llocks[NUMCPUS];
    int threshold;
} counter_t;

typedef struct {
    counter_t * counter;
    int iterations;
    int i;
} arg_t;

void init_counter(counter_t* counter, int threshold) {
    counter->count = 0;
    counter->threshold = threshold;
    pthread_mutex_init(&counter->glock, NULL);
    for(int i = 0; i<NUMCPUS; i++) {
        pthread_mutex_init(&counter->llocks[i], NULL);
        counter->locals[i] = 0;
    }
}

void inc_counter(counter_t* counter, int thread_id) {
    int lock_id = thread_id % NUMCPUS;
    pthread_mutex_lock(&counter->llocks[lock_id]);
    counter->locals[lock_id]+=1;
    if(counter->locals[lock_id] > counter->threshold) {
        pthread_mutex_lock(&counter->glock);
        counter->count += counter->locals[lock_id];
        counter->locals[lock_id] = 0;
        pthread_mutex_unlock(&counter->glock);
    }
    pthread_mutex_unlock(&counter->llocks[lock_id]);
}

int get_count(counter_t* counter) {
    int ret = -1;
    pthread_mutex_lock(&counter->glock);
    ret = counter->count;
    pthread_mutex_unlock(&counter->glock);
    return ret;
}

void* inc(void* args) {
    arg_t* arg = (arg_t*) args;
    struct timeval t1;
    gettimeofday(&t1, NULL);
    for(int i = 0;i<arg->iterations; i++) {
        inc_counter(arg->counter, arg->i);
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    // printf("Thread #%d: %f\n", arg->i, get_dt(&t1, &t2));
    return NULL;
}

int main(int argc, char** argv) {
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    int number_of_threads = argc >= 1 ? atoi(argv[1]) : 4;
    int iterations = argc >= 2 ? atoi(argv[2]) : 1e6;
    int threshold = argc >= 4 ? atoi(argv[3]) : 16;

    counter_t counter;
    init_counter(&counter, threshold);

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
