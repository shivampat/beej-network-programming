#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: showip <hostname>\n");
        return 1;
    }

    char* hostname = argv[1];

    int status;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    struct addrinfo *results, *res_p;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(hostname, NULL, &hints, &results)) != 0) {
        fprintf(stderr, "Error with getaddrinfo.\n");
        exit(1);
    }

    // Results is the head of the linked list that has all the results.
    for (res_p = results; res_p != NULL; res_p = res_p->ai_next) {
        // if addr family is ipv4
        struct sockaddr* addr = res_p->ai_addr;
        char ipv4[INET_ADDRSTRLEN]; 
        char ipv6[INET6_ADDRSTRLEN]; 

        if (res_p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4_addr = (struct sockaddr_in*) addr;
            if (inet_ntop(res_p->ai_family, &(ipv4_addr->sin_addr), ipv4, INET_ADDRSTRLEN) == NULL) {
                fprintf(stderr, "Error with network to presentation conversion.\n");
                exit(1);
            }
            printf("IPv4: %s\n", ipv4);
        }
        else {
            struct sockaddr_in6* ipv6_addr = (struct sockaddr_in6*) addr;
            if (inet_ntop(res_p->ai_family, &(ipv6_addr->sin6_addr), ipv6, INET6_ADDRSTRLEN) == NULL) {
                fprintf(stderr, "Error with network to presentation conversion.\n");
                exit(1);
            }
            printf("IPv6: %s\n", ipv6);
        }

    }

    freeaddrinfo(results);
}