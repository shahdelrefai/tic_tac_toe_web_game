#include "mysocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createTCP_IPv4_Socket() { return socket(AF_INET, SOCK_STREAM, 0); }

struct sockaddr_in* create_IPv4_address(char *ip, int port) {
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if(strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

void DoServerClientProcedures(int* serverSocketFD, struct sockaddr_in* serverAddress, int* clientSocketFD)
{
    *serverSocketFD = createTCP_IPv4_Socket();
    serverAddress = create_IPv4_address("", 2176);

    int result;
    do{
        result = bind(*serverSocketFD, (const struct sockaddr *) serverAddress, sizeof (*serverAddress));
    }while(result != 0);
    printf("bound was successful\n");

    listen(*serverSocketFD,1);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof (struct sockaddr_in);
    *clientSocketFD = accept(*serverSocketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);

    char buffer[1024];
    recv(*clientSocketFD, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);
    return;
}

