#define _DEFAULT_SOURCE
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*

simple_server.c

A simple server that incorporates socket(), connect(), send(), and recv()

*/

#define PORTNUM 3490

int main() {

    // Establish port connection
    struct addrinfo hints, *res, *res_p;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status;
    if ((status = getaddrinfo(NULL, PORTNUM, &hints, &res)) != 0) {
        
    }
}