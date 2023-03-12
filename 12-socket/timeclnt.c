#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void oops(char *msg) {
    perror(msg);
    exit(1);
}

int main(int ac, char **av) {
    assert(ac == 3);

    int clnt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_fd == -1) {
        oops("socket");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(atoi(av[2]));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (-1 == connect(clnt_fd, (struct sockaddr *)&server_addr,
                      sizeof(server_addr))) {
        oops("connect");
    }

    char buf[BUFSIZ] = {'\0'};
    int len = read(clnt_fd, buf, BUFSIZ);
    if (len == -1) {
        oops("read");
    }
    if (len != write(1, buf, len)) {
        oops("write");
    }

    close(clnt_fd);
}