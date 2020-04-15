
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <aio.h>
#include <signal.h>

#define PORT 8080
#define BUFF_SIZE 1024
#define FILE_BUFFER_SIZE  1 << 20 // 1 MB

#define IO_SIGNAL SIGUSR1

char buffer[BUFF_SIZE] = {0};
char file_buff[FILE_BUFFER_SIZE];
char replay[BUFF_SIZE + 32];

fd_set activeFDs; // the fds we are going to look for inputs


struct io_request {
    int connection_fd;
    struct aiocb* cb;
};

void trimnewline(char* s) {
    int i = 0;
    while(i < BUFF_SIZE) {
        if(s[i] == '\r' || s[i] == '\n') {
            s[i] = '\0';
            return;
        }
        i++;
    }
}

void get_greeting(char* buff) {
    time_t now;
    time(&now);
    struct tm* time_info = localtime(&now);
    strftime(buff, BUFF_SIZE,
            "\nHenlo!\nServer time: %d %b %Y %H:%M:%S\n\n",
            time_info);
}

void send_greetings(int fd) {
    get_greeting(buffer);
    send(fd, buffer, strlen(buffer), 0);
}

int read_and_serve(int fd) {
    read(fd, buffer, sizeof(buffer));
    trimnewline(buffer);

    int f_fd = open(buffer, O_RDONLY);
    if (f_fd < 0) {
        sprintf(replay, "Failed to open file `%s`\n", buffer);
        send(fd, replay, strlen(replay), 0);
        return 0;
    }
    struct io_request* req = malloc(sizeof(struct io_request));
    req->connection_fd = fd;
    req->cb = malloc(sizeof(struct aiocb));
    req->cb->aio_fildes = f_fd;
    req->cb->aio_offset = 0;
    req->cb->aio_buf = malloc(FILE_BUFFER_SIZE);
    req->cb->aio_nbytes = FILE_BUFFER_SIZE;
    req->cb->aio_reqprio = 0;
    req->cb->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    req->cb->aio_sigevent.sigev_signo = IO_SIGNAL;
    req->cb->aio_sigevent.sigev_value.sival_ptr = req;

    aio_read(req->cb);
    return 0;
}

static void aio_handler(int signo, siginfo_t* si, void* ucontext) {
    if (si->si_code != SI_ASYNCIO) return;
    struct io_request* req = si->si_value.sival_ptr;

    send(req->connection_fd, (const void*) req->cb->aio_buf, req->cb->aio_nbytes, 0);

    // close connection
    FD_CLR(req->connection_fd, &activeFDs);
    shutdown(req->connection_fd, SHUT_RDWR);

    // free up allocated memory
    free(req->cb->aio_buf);
    free(req->cb);
    free(req);
}

int main(int argc, char** argv) {
    // set up signaling
    struct sigaction sa;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = aio_handler;
    sigaction(IO_SIGNAL, &sa, NULL);
    // signal(IO_SIGNAL, aio_handler);

    // address for the socket
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // set up the socket
    int socket_fd, opt = 1;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(socket_fd, (struct sockaddr*) &address, addrlen);
    listen(socket_fd, 3);

    FD_ZERO(&activeFDs);

    // this main socket fd is one of them
    FD_SET(socket_fd, &activeFDs);

    while(1) {
        fd_set readFDs = activeFDs; // copy
        select(FD_SETSIZE, &readFDs, NULL, NULL, NULL);
        for(int fd = 0; fd < FD_SETSIZE; fd++) {
            if (!FD_ISSET(fd, &readFDs)) continue;

            if (fd == socket_fd) {
                // input in the main socket fd, means new connect
                // accept it
                int new_connection = accept(fd, (struct sockaddr*) &address, &addrlen);
                // send greetings
                send_greetings(new_connection);
                // add this new connection fd to the active fds
                FD_SET(new_connection, &activeFDs);
            } else {
                // input in a already connected connection fd
                // read and serve, close if necessary
                int close = read_and_serve(fd);
                if (close) {
                    FD_CLR(fd, &activeFDs); // don't monitor this fd anymore
                    shutdown(fd, SHUT_RDWR);
                }
            }
        }
    }
    return 0;
}
