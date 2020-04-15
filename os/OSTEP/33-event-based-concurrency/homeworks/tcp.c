
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define PORT 8080
#define BUFF_SIZE 1024

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
            "\nHenlo!\nServer time: %d %b %Y %H:%M\n\n",
            time_info);
}

int main(int argc, char** argv) {
    char buffer[BUFF_SIZE] = {0};
    char replay[BUFF_SIZE + 16];

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

    // prepare socket to take connections
    listen(socket_fd, 3);

    while(1) {
        // accept a connection
        int connection_fd = accept(socket_fd, (struct sockaddr*) &address, &addrlen);
        get_greeting(buffer);
        send(connection_fd, buffer, strlen(buffer), 0);
        // keep replaying until "bye" is received
        while (1) {
            read(connection_fd, buffer, sizeof(buffer));
            trimnewline(buffer);

            if (strcmp(buffer, "bye") == 0) {
                break;
            }

            sprintf(replay, "%s you\n", buffer);
            send(connection_fd, replay, strlen(replay), 0);
        }
        // close the connection
        shutdown(connection_fd, SHUT_RDWR);
    }
    return 0;
}
