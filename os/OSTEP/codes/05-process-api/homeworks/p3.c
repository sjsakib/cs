#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
    } else if (rc == 0) {
        printf("Hello!\n");
    } else {
        fopen("xxxx", "w");
        printf("Goodbye!\n");
    }
    return 0;
}
