#ifndef HTTP_H
#define HTTP_H


/* Only POST is available */
typedef enum
{
    POST,
}Http_Type;


/*
    Creates a HTTP request string, that can be sent to a server.
    
    Returns: a char* on the heap (needs to be freed)
*/
char* http_create_request(Http_Type type, const char* data, const char* api_gateway);

#endif