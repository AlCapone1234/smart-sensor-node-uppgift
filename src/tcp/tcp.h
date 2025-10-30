#ifndef TCP_H
#define TCP_H

#include <stdio.h>


/*
    Reads whole message from socket and returns it as char* with its whole correct size (no memory above what is needed is used)
    
    WARNING: The returned value needs to be freed
*/
char* tcp_read(int socket_to_read_from, size_t max_buffer_len);


#endif