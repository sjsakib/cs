#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *lsargs[3];
    lsargs[0] = strdup("/bin/ls");
    lsargs[1] = strdup("-l");
    lsargs[2] = NULL;
    int rc = fork();
    if (rc == 0) {
        // execl(lsargs[0], lsargs[0], lsargs[1], NULL);
        // execle(lsargs[0], lsargs[0], lsargs[1], NULL, NULL);
        // execlp("ls", lsargs[1], lsargs[1], NULL);
        // execv(lsargs[0], lsargs);
        // execvp("ls", lsargs);
        execvpe("ls", lsargs, NULL);
    } else {
        return -1;
    }
    return 0;
}
