#include <stdio.h>
#include "common.h"


int main(int argc, char** argv) {
    int sd = UDP_Open(8080);
    struct sockaddr_in addrSend, addrRcv;
    UDP_FillSockAddr(&addrSend, "localhost", 8000);
    char msg[BUFFER_SIZE];
    sprintf(msg, "Hello Server!");
    UDP_Write(sd, &addrSend, msg, BUFFER_SIZE);
    UDP_Read(sd, &addrRcv, msg, BUFFER_SIZE);
    printf("Received: %s\n", msg);
    return 0;
}