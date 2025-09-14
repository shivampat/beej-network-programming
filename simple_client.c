#define _DEFAULT_SOURCE
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*

simple_client.c

A simple client application that allows messages to be sent to the server
hosted on simple_server.c

*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage simple_client <hostname> <port>");
        exit(1);
    }

    char *HOSTNAME = argv[1];
    int PORTNUM = atoi(argv[2]);

    // Establish port connection
    struct addrinfo hints, *res, *res_p;


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(HOSTNAME, PORTNUM, &hints, &res)) != 0) {
       fprintf(stderr, "Error with getaddrinfo: %s\n", gai_strerror(status)); 
       exit(1);
    }

    // Get working socket file descriptor 
    int sock_fd = 0;
    for (res_p = res; res_p != NULL; res_p = res_p->ai_next) {
        sock_fd = socket(res_p->ai_family, res_p->ai_socktype, res_p->ai_protocol);

        char ipaddr[INET6_ADDRSTRLEN];
        if (res_p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4addr = (struct sockaddr_in*) (res_p->ai_addr);
            if (inet_ntop(res_p->ai_family, &(ipv4addr->sin_addr), ipaddr, INET6_ADDRSTRLEN) == NULL) {
                fprintf(stderr, "Error in network to presentation conversion!\n");
                exit(1);
            } 
        }
        else {
            struct sockaddr_in6* ipv6addr = (struct sockaddr_in6*) (res_p->ai_addr);
            if (inet_ntop(res_p->ai_family, &(ipv6addr->sin6_addr), ipaddr, INET6_ADDRSTRLEN) == NULL) {
                fprintf(stderr, "Error in network to presentation conversion!\n");
                exit(1);
            } 
        }

        printf("Attempting to open socket at %s\n", ipaddr);

        if (sock_fd != -1) {
            printf("Socket created at fd: %d\n", sock_fd);
            break;
        }
    }

    // Connect to socket
    int conn_err = 0;
    if ((conn_err = connect(sock_fd, res_p->ai_addr, res_p->ai_addrlen)) != 0) {
        fprintf(stderr, "Error connecting to socket: %s\n", gai_strerror(conn_err));
        exit(1);
    }



}