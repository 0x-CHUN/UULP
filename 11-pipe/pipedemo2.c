#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHILD_MSG "I want a cookie!\n"
#define PAR_MSG "Testing..\n"
#define oops(m, x)                                                             \
    {                                                                          \
        perror(m);                                                             \
        exit(x);                                                               \
    }

int main(int argc, char const *argv[]) {
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;
    if (pipe(pipefd) == -1) {
        oops("Cannot get a pipe", 1);
    }
    switch (fork()) {
    case -1:
        oops("cannot fork", 2);
        break;
    case 0:
        len = strlen(CHILD_MSG);
        while (1) {
            if (write(pipefd[1], CHILD_MSG, len) != len) {
                oops("write", 3);
            }
            sleep(5);
        }
        break;
    default:
        len = strlen(PAR_MSG);
        while (1) {
            if (write(pipefd[1], PAR_MSG, len) != len) {
                oops("write", 4);
            }
            sleep(1);
            read_len = read(pipefd[0], buf, 100);
            printf("read_len: %d\n", read_len);
            if (read_len < 0) {
                exit(1);
            } else if (read_len == 0) {
                break;
            }
            write(1, buf, read_len);
        }
    }
    return 0;
}
