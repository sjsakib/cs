#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int arc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        printf("failed to fork\n");
    } else if(rc == 0) {
        int child_wait_rc = wait(NULL);
        printf("Child child_wait_rc: %d (pid: %d)\n", child_wait_rc, (int) getpid() );
    } else {
        int wait_rc = wait(NULL);
        printf("Parent, wait_rc: %d (pid: %d)\n", wait_rc, (int) getpid());
    }

    return 0;

}