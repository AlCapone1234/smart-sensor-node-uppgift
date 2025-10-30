#include <stdio.h>
#include "client/client.h"
#include "server/server.h"

int main(void)
{
    #ifdef TCPCLIENT
        client_initialize();
    #else
        server_initialize();
    #endif

    return 0;
}