#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct {int a; int b;} myarg_t;
typedef struct {int x; int y;} myret_t;

void *mythread(void *args) {
    myarg_t *arg = args;
    printf("Received: %d %d\n", arg->a, arg->b);

    myret_t *ret = malloc(sizeof(myret_t));
    return ret;
}

int main(int argc, char** argv) {
    pthread_t p;
    myret_t *rvals;
    myarg_t args = {10, 20};
    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void**) &rvals);
    printf("returned: %d %d\n", rvals->x, rvals->y);
    return 0;
}