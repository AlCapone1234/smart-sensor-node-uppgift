#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

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

    char buffer[1024];
    ssize_t totalBytesRead = 0;
    while (1)
    {
        ssize_t bytesRead = recv(clientSocket, &buffer[totalBytesRead], 1024, 0);

        if (bytesRead < 0)
        {
            break;
        }

        if (bytesRead == 0)
        {
            break;
        }

        totalBytesRead += bytesRead;
    }
    buffer[totalBytesRead] = '\0';

    printf("%s\n", buffer);
}