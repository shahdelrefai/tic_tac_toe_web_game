//
// Created by Shahd El-Refai on 02/09/2023.
//

#ifndef SOCKETSERVER_MYSOCKET_H
#define SOCKETSERVER_MYSOCKET_H

int createTCP_IPv4_Socket();
struct sockaddr_in* create_IPv4_address(char *ip, int port);

void DoServerClientProcedures(int* serverSocketFD, struct sockaddr_in* serverAddress, int* clientSocketFD);

#endif //SOCKETSERVER_MYSOCKET_H
