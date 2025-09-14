#define _DEFAULT_SOURCE
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

/*

simple_server.c

A simple server that incorporates socket(), connect(), send(), and recv()

*/

#define PORTNUM "6741"
#define BACKLOG 10

int main() {

    // Establish port connection
    struct addrinfo hints, *res, *res_p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(NULL, PORTNUM, &hints, &res)) != 0) {
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

    // Error handling if no socket is found or no results.
    if (sock_fd == 0 || sock_fd == -1 || res_p == NULL) {
        fprintf(stderr, "Socket cannot be created at the given port.\n");
        exit(1);
    }

    // Binding portnum to IP address found.
    int bind_errno = 0;
    if ((bind_errno = bind(sock_fd, res_p->ai_addr, res_p->ai_addrlen)) != 0) {
        fprintf(stderr, "Error binding port to address: %s\n", gai_strerror(bind_errno));
        exit(1);
    }

    printf("Bound to port %s\n", PORTNUM);

    // Set up listener to current socket connection
    int list_errno = 0;
    if ((list_errno = listen(sock_fd, BACKLOG)) != 0) {
        fprintf(stderr, "Error starting listener: %s\n", gai_strerror(list_errno));
        exit(1);
    }

    // Loop to accept connections.
    struct sockaddr_storage client_addr;
    int client_addr_len = sizeof(client_addr);

    // Keep attemping accepts until it works.
    int conn_fd;
    while (true) {
        conn_fd = accept(sock_fd, (struct sockaddr*) &(client_addr), &client_addr_len);

        if (conn_fd >= 0)
            break;

        printf("No clients. Waiting 10 seconds to check again.");
    }

    printf("Client connection opened at fd: %d\n", conn_fd);
    printf("Sending message to client.\n");

    char *msg = "Hello, client!\n";
    int len = strlen(msg);

    int bytes_sent = send(conn_fd, msg, len, 0);

    close(sock_fd);
    close(conn_fd);


    freeaddrinfo(res);
}