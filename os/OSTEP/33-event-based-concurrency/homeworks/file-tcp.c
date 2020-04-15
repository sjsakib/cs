
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>


#define PORT 8080
#define BUFF_SIZE 1024
#define FILE_BUFFER_SIZE  1 << 20 // 1 MB

char buffer[BUFF_SIZE] = {0};
char file_buff[FILE_BUFFER_SIZE];
char replay[BUFF_SIZE + 16];

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
    int nbytes = read(f_fd, file_buff, sizeof(file_buff));
    file_buff[nbytes] = '\0';

    send(fd, file_buff, strlen(file_buff), 0);
    return 1;
}

int main(int argc, char** argv) {
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

    fd_set activeFDs; // the fds we are going to look for inputs
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
