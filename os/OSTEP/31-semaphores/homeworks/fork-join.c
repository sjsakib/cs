#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

sem_t s; 

void *child(void *arg) {
    sleep(1);
    printf("child\n");
    Sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    Sem_init(&s, 0);
    Pthread_create(&p, NULL, child, NULL);
    Sem_wait(&s);
    printf("parent: end\n");
    return 0;
}

