#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int status; 
    struct addrinfo hints;
    struct addrinfo *res; // linked list for results

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC; // Allows both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // For wildcard IP address

    if ((status = getaddrinfo("www.google.com", NULL, &hints, &res) != 0)) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }

    // servinfo now points to a linked list of 1 or more
    // struct addrinfos

    // for (struct addrinfo* currRes = res; currRes != NULL; currRes = res->ai_next)  
        printf("IP addr: %s\n", res->ai_addr->sa_data);

    // ... do everything until you don't need servinfo anymore ....

    freeaddrinfo(res); // free the linked-list        

}