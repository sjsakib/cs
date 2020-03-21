#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen("p2.output", "w");
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
    } else if (rc ==0) {
        fprintf(fp, "Hello from child.\n");
    } else {
        fprintf(fp, "Hello from parent.\n");
    }
    return 0;
}
