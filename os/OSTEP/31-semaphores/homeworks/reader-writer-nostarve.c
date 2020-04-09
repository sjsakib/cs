#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common_threads.h"

//
// Your code goes in the structure and functions below
//

typedef struct __rwlock_t {
    sem_t countlock;
    sem_t waitinglock;
    sem_t writelock;
    sem_t read_sem;

    int readers;
    int writer_waiting;
} rwlock_t;


void rwlock_init(rwlock_t *rw) {
    Sem_init(&rw->writelock, 1);
    Sem_init(&rw->countlock, 1);
    Sem_init(&rw->waitinglock, 1);
    Sem_init(&rw->read_sem, 0);
    rw->readers = 0;
    rw->writer_waiting = 0;
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    Sem_wait(&rw->countlock);
    
    
    Sem_wait(&rw->waitinglock);
    if(rw->writer_waiting >= 1) {
        Sem_post(&rw->writelock);
        Sem_post(&rw->waitinglock);

        Sem_wait(&rw->read_sem);
        Sem_wait(&rw->writelock);
    } else {
        Sem_post(&rw->waitinglock);
    }

    if(rw->readers == 0) {
        Sem_wait(&rw->writelock);
    }
    rw->readers++;
    Sem_post(&rw->countlock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    Sem_wait(&rw->countlock);
    if(rw->readers == 1) {
        Sem_post(&rw->writelock);
    }
    rw->readers--;
    Sem_post(&rw->countlock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    Sem_wait(&rw->waitinglock);
    rw->writer_waiting++;
    Sem_post(&rw->waitinglock);

    Sem_wait(&rw->writelock);

    Sem_wait(&rw->waitinglock);
    rw->writer_waiting--;
    Sem_post(&rw->waitinglock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    Sem_post(&rw->read_sem);
    Sem_post(&rw->writelock);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void *reader(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_readlock(&lock);
	printf("read %d\n", value);
	rwlock_release_readlock(&lock);
    }
    return NULL;
}

void *writer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
	rwlock_acquire_writelock(&lock);
	value++;
	printf("write %d\n", value);
	rwlock_release_writelock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);
    loops = atoi(argv[3]);

    pthread_t pr[num_readers], pw[num_writers];

    rwlock_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < num_readers; i++)
	Pthread_create(&pr[i], NULL, reader, NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_create(&pw[i], NULL, writer, NULL);

    for (i = 0; i < num_readers; i++)
	Pthread_join(pr[i], NULL);
    for (i = 0; i < num_writers; i++)
	Pthread_join(pw[i], NULL);

    printf("end: value %d\n", value);

    return 0;
}

