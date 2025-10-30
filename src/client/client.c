#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "../tcp/tcp.h"

#include "../server/server.h"

void client_initialize()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddress = {0};

    /*As I am using C89, getaddrinfo is not available*/
    struct hostent* server;

    server = gethostbyname("www.httpbin.org");
    if (server == NULL)
    {
        printf("Failed to get hostname");
        return;
    }

    serverAddress.sin_family = AF_INET;
    /*serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");*/
    serverAddress.sin_port = htons(80);
    memcpy(&serverAddress.sin_addr.s_addr, server->h_addr_list[0], server->h_length);

    if (connect(fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("connect");
        close(fd);
        return;
    }

    char *message = 
        "POST /post HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 62\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{\"device\":\"UUID\",\"time\":\"<time>\",\"temperature\":\"<temperature>C\"}";

    if (send(fd, message, strlen(message), 0) < 0)
    {
        perror("Send failed");
        close(fd);
        return;
    }

    char* msg = tcp_read(fd, 1024);

    if (msg == NULL)
    {
        printf("TCP_READ FAILED!\n");
        close(fd);
        return;
    }

    printf("%s\n", msg);

    free(msg);
    close(fd);
}