#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 13000

void oops(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char const *argv[]) {
    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_fd == -1) {
        oops("socket");
    }
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sockaddr.sin_port = htons(PORT);
    sockaddr.sin_family = AF_INET;
    if (bind(serv_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) {
        oops("bind");
    }

    if (listen(serv_fd, 1) != 0) {
        oops("listen");
    }
    int client_fd = -1;
    FILE *client_fp = NULL;
    time_t the_time = 0;
    while (1) {
        client_fd = accept(serv_fd, NULL, NULL);
        printf("Wow! got a call\n");

        if (client_fd == -1) {
            oops("accept");
        }

        client_fp = fdopen(client_fd, "w");
        if (client_fp == NULL) {
            oops("fdopen");
        }

        the_time = time(NULL);

        fprintf(client_fp, "The time here is ..");
        fprintf(client_fp, "%s", ctime(&the_time));
        fclose(client_fp);
    }
    return 0;
}
