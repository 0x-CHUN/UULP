#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int len, p[2];
    char buf[BUFSIZ];
    if (pipe(p) == -1) {
        perror("could not make pipe");
        exit(1);
    }
    printf("Get a pipe! It is file descriptors: {%d %d}\n", p[0], p[1]);
    while (fgets(buf, BUFSIZ, stdin)) {
        len = strlen(buf);
        if (write(p[1], buf, len) != len) {
            perror("Writing to pipe!");
            break;
        }
        for (int i = 0; i < len; i++) {
            buf[i] = 'X';
        }
        len = read(p[0], buf, BUFSIZ);
        if (len == -1) {
            perror("Reading from pipe");
            break;
        }
        if (write(1, buf, len) != len) {
            perror("Writing to stdout");
            break;
        }
    }
    return 0;
}
