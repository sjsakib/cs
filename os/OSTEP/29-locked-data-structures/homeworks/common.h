#include <sys/time.h>

float get_dt(struct timeval *t1, struct timeval *t2) {
    return (t2->tv_sec - t1->tv_sec) + (t2->tv_usec - t1->tv_usec) / (float)1e6;
}

int get_dt_n(struct timeval *t1, struct timeval *t2) {
    return (t2->tv_sec - t1->tv_sec)*1e6 + (t2->tv_usec - t1->tv_usec);
}
