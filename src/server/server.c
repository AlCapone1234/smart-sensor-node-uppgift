#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include "../tcp/tcp.h"
#include "server.h"

void server_initialize()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) 
    {
        perror("socket");
        return;
    }
    
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("bind");
        return;
    }

    if (listen(serverSocket, 5) == -1)
    {
        perror("listen");
        return;
    }

    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);

    if (clientSocket == -1)
    {
        perror("accept");
        return;
    }

    char* message = tcp_read(clientSocket, 1024);

    printf("%s\n", message);

    free(message);
    message = NULL;
}