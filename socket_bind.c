#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    struct addrinfo hints, *res, *res_p;
    int sock_fd = -1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int err_code = 0;
    if ((err_code = getaddrinfo("www.google.com", "3490", &hints, &res)) != 0) {
        fprintf(stderr, "Error with getaddrinfo: %s\n", gai_strerror(err_code));
        exit(1);
    }

    for (res_p = res; res_p != NULL; res_p = res_p->ai_next) {
        struct sockaddr* addr_p = res_p->ai_addr;

        sock_fd = socket(res_p->ai_family, res_p->ai_socktype, res_p->ai_protocol);
        if (sock_fd != -1) 
            break;

        // if (res_p->ai_family == AF_INET) {
        //     struct sockaddr_in *addr_ipv4 = (struct sockaddr_in*) addr_p;
        // }
        // else {
        //     struct sockaddr_in6 *addr_ipv6 = (struct sockaddr_in6*) addr_p;
        // }
    }

    printf("Socket fd: %d\n", sock_fd);

    return 0;
}