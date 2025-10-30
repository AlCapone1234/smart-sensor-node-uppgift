#include <stdio.h>
#include "client/client.h"
#include "server/server.h"
#include <string.h>

void on_response(const char* response)
{
    printf("Callback response:\n");
    printf("%s\n", response);
}

void print_no_arguments()
{
    printf("./main <client> or ./main <server> to run!\n");
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        print_no_arguments();
        return -1;
    }

    if (strcmp(*(argv+1), "client") == 0)
    {
        printf("Running Client!\n");
        client_initialize(on_response);
    } 
    else if (strcmp(*(argv+1), "server") == 0)
    {
        printf("Running Server!\n");
        server_initialize();
    }
    else
    {
        print_no_arguments();
        return -1;
    }
    return 0;
}