#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    int turn;
    int count;
    sem_t lock;
    sem_t turnlock;
} ns_mutex_t;

ns_mutex_t m;

void ns_mutex_init(ns_mutex_t *m) {
    Sem_init(&m->lock, 1);
    Sem_init(&m->turnlock, 1);
    m->turn = 1;
    m->count = 0;
}

void ns_mutex_acquire(ns_mutex_t *m) {
    Sem_wait(&m->turnlock);
    int turn = ++m->count;
    while (turn != m->turn) {
        Sem_post(&m->turnlock);
        Sem_wait(&m->lock);
        Sem_wait(&m->turnlock);
    }
    Sem_post(&m->turnlock);
}

void ns_mutex_release(ns_mutex_t *m) {
    Sem_wait(&m->turnlock);
    m->turn++;
    Sem_post(&m->lock);
    Sem_post(&m->turnlock);
}


void *worker(void *arg) {
    printf("Started: %lu\n", pthread_self());
    ns_mutex_acquire(&m);
    printf("Got lock: %lu\n", pthread_self());
    ns_mutex_release(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    ns_mutex_init(&m);
    pthread_t threads[10];
    for(int i = 0; i < 10; i++) {
        Pthread_create(&threads[i], NULL, worker, NULL);
    }
    for(int i = 0; i < 10; i++) {
        Pthread_join(threads[i], NULL);
    }
    printf("parent: end\n");
    return 0;
}

