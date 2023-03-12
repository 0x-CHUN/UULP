#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define HOSTNAME_LEN 64
#define BACKLOG 1

int make_server_socket(uint16_t portnum, int backlog) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(portnum);
    server_addr.sin_family = AF_INET;

    char hostname[HOSTNAME_LEN];
    memset(hostname, 0, HOSTNAME_LEN);
    gethostname(hostname, HOSTNAME_LEN);
    struct hostent *hp = gethostbyname(hostname);
    if (hp == NULL || hp->h_addrtype != AF_INET) {
        return -1;
    }
    memcpy(&server_addr.sin_addr, hp->h_addr_list[0], hp->h_length);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) !=
        0) {
        return -1;
    }
    if (listen(server_fd, backlog) != 0) {
        return -1;
    }

    return server_fd;
}
int connect_to_server(char *hostname, uint16_t port_num) {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        return -1;
    }

    struct hostent *hp = gethostbyname(hostname);
    if (hp == NULL || hp->h_addrtype != AF_INET) {
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memcpy(&server_addr.sin_addr, hp->h_addr_list[0], hp->h_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);

    if (connect(client_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) != 0) {
        return -1;
    }

    return client_fd;
}
