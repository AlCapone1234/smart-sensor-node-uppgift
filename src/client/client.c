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
#include "../http/http.h"
#include "../server/server.h"
#include "client.h"

void client_work(Client* client, ResponseCallback callback);


void client_initialize(ResponseCallback response)
{
    Client client = {0};

    client.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client.fd == -1)
    {
        perror("socket");
        return;
    }

    client.server = gethostbyname("www.httpbin.org");
    if (client.server == NULL)
    {
        printf("Failed to get hostname");
        return;
    }

    client.serverAddress.sin_family = AF_INET;
    client.serverAddress.sin_port = htons(80);
    memcpy(&client.serverAddress.sin_addr.s_addr, client.server->h_addr_list[0], client.server->h_length);

    client_work(&client, response);
}

void client_work(Client* client, ResponseCallback callback)
{
    if (connect(client->fd, (struct sockaddr*)&client->serverAddress, sizeof(client->serverAddress)) == -1)
    {
        perror("connect");
        close(client->fd);
        return;
    }

    char* message = http_create_request(POST, "{\"device\":\"UUID\",\"time\":\"<time>\",\"temperature\":\"<temperature>C\"}", "post");
    if (message == NULL)
    {
        return;
    }

    if (send(client->fd, message, strlen(message), 0) < 0)
    {
        perror("Send failed");
        close(client->fd);
        return;
    }

    char* server_read_data = tcp_read(client->fd, 1024);
    if (server_read_data == NULL)
    {
        printf("TCP_READ FAILED!\n");
        close(client->fd);
        return;
    }

    if (callback)
    {
        callback(server_read_data);   
    }

    free(server_read_data);
    free(message);
    server_read_data = NULL;
    message = NULL;
    close(client->fd);
}