#include <stdio.h>
#include <math.h>
#include <pthread.h>

long double term(unsigned long long i) {
    long double t = (1.0/i)*(1.0/i);
    printf("%Lf\n", t);
    return t;
}

long double range(unsigned long long i, unsigned long long j) {
    long double sum = 0;
    for(unsigned long long k = i; k < j; k++) {
        sum+=term(k);
        // printf("%lld %Lf\n",k, sum);
        if (sum == INFINITY) return sum;
    }
    
    return sum;
}

int main(int argc, char **argv) {
    long double sum = range(1, 10000000);
    printf("%Lf %Lf\n",sum, sqrtl(sum*(long double)6.0));
    return 0;
}
