#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcp.h"

char* tcp_read(int socket_to_read_from, size_t max_buffer_len)
{
    char buffer[max_buffer_len];
    ssize_t totalBytesRead = 0;
    while (1)
    {
        ssize_t bytesRead = recv(socket_to_read_from, &buffer[totalBytesRead], max_buffer_len, 0);

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

    char* fullMessage = (char*)malloc(totalBytesRead * sizeof(char)); 

    if (fullMessage == NULL)
        return NULL;

    memcpy(fullMessage, buffer, totalBytesRead);

    return fullMessage;
}
