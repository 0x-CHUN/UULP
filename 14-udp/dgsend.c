#include "dgram.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

void oops(char *);

int main(int ac, char *av[]) {
    if (ac != 4) {
        fprintf(stderr, "usage: ./dgsend hostname port_num message");
        exit(1);
    }
    int client_fd = make_dgram_client_socket();
    if (client_fd == -1) {
        oops("socket");
    }
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    make_internet_address(av[1], (uint16_t)atoi(av[2]), &server_address);

    if (-1 == sendto(client_fd, av[3], strlen(av[3]), 0,
                     (struct sockaddr *)&server_address,
                     sizeof(server_address))) {
        oops("sendto failed");
    }

    return 0;
}

void oops(char *msg) {
    perror(msg);
    exit(1);
}