#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../server/server.h"

void client_initialize()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(SERVER_PORT);

    if (connect(fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("connect");
        close(fd);
        return;
    }

    char* message = "Hello On The Server";

    if (send(fd, message, strlen(message), 0) < 0)
    {
        perror("Send failed");
        close(fd);
        return;
    }
}