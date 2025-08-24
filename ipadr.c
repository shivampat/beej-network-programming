#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    char ip[INET_ADDRSTRLEN];
    struct sockaddr_in sa;

    inet_ntop(AF_INET, &(sa.sin_addr), ip, INET_ADDRSTRLEN); 
    printf("IP address: %s\n", ip);

}