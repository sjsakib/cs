#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int arc, char *argv[]) {
    int pfd[2];
    
    if (pipe(pfd) < 0) {
        fprintf(stderr, "Pipe failed\n");
    }
    
    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "failed to fork\n");
    } else if(rc1 == 0) {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        execlp("grep", "grep", "fork", "p8.c", NULL);
    } else {
        int rc2 = fork();

        if (rc2 < 0) {
            printf("Second fork failed\n");
        } else if (rc2 == 0) {
            close(pfd[1]);
            dup2(pfd[0], STDIN_FILENO);
            execlp("wc", "wc", "-l", NULL);
        } else {
            // waitpid((pid_t) rc2, NULL, WUNTRACED);
            // wait(NULL);
            printf("Parent (pid: %d)\n", (int) getpid());
        }
    }

    return 0;

}
