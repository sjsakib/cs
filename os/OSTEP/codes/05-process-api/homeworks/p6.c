#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int arc, char *argv[]) {
    int rc1 = fork();

    if (rc1 < 0) {
        printf("failed to fork\n");
    } else if(rc1 == 0) {
        printf("Child 1 (pid: %d)\n", (int) getpid() );
    } else {
        int rc2 = fork();

        if (rc2 < 0) {
            printf("Second fork failed\n");
        } else if (rc2 == 0) {
            printf("Child 2 (pid: %d)\n", (int) getpid());
        } else {
            waitpid((pid_t) rc2, NULL, WNOHANG);
            // wait(NULL);
            printf("Parent (pid: %d)\n", (int) getpid());
        }
    }

    return 0;

}