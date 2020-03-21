#include <stdio.h>
#include <unistd.h>

int var;

int main(int argc, char *argv[]) {
    var = 42;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
    } else if (rc ==0) {
        // var = 41;
        printf("var: %d, in child (pid: %d)\n", var, (int) getpid());
    } else {
        var = 43;
        printf("var: %d, in parent (pid: %d)\n", var, (int) getpid());
    }
    return 0;
}
