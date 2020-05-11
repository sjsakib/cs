#include <stdio.h>
#include "common.h"

int main(int argc, char** argv) {
    int sd = UDP_Open(8000);
    struct sockaddr_in addrRcv;
    char msg[BUFFER_SIZE];
    while(1) {
        UDP_Read(sd, &addrRcv, msg, BUFFER_SIZE);
        printf("Received: %s\n", msg);
        sprintf(msg, "Hi client!");
        UDP_Write(sd, &addrRcv, msg, BUFFER_SIZE);
    }
    return 0;
}