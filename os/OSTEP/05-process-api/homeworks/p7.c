#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int arc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        printf("failed to fork\n");
    } else if(rc == 0) {
        printf("Child\n");
        // fflush(stdout);
        close(STDOUT_FILENO);
        printf("Child (pid: %d)\n", (int) getpid() );
    } else {
        int wait_rc = wait(NULL);
        printf("Parent, wait_rc: %d (pid: %d)\n", wait_rc, (int) getpid());
    }

    return 0;

}