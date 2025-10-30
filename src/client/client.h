#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef void (*ResponseCallback)(const char* response);

void client_initialize(ResponseCallback response);

typedef struct 
{
    int fd;
    struct sockaddr_in serverAddress;
    struct hostent* server;
}Client;

void client_work(Client* client, ResponseCallback callback);

#endif