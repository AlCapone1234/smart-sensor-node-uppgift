#include "http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* http_message_template = 
        "%s /%s HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{%s}";


char* http_type_to_str(Http_Type type)
{
    switch (type)
    {
    case POST:
        return "POST";
        break;
    default: 
        return NULL;
        break;
    }
}

/*\"device\":\"UUID\",\"time\":\"<time>\",\"temperature\":\"<temperature>C\"*/

char* http_create_request(Http_Type type, const char* data, const char* api_gateway)
{
    char* type_identifier = http_type_to_str(type);
    size_t dataLength = strlen(data);
    size_t size = dataLength + strlen(type_identifier) + strlen(http_message_template) + strlen(api_gateway) - 3;

    char* buffer = (char*)malloc(size * sizeof(char)); 
    sprintf(buffer, http_message_template, type_identifier, api_gateway, dataLength, data);

    return buffer;
}