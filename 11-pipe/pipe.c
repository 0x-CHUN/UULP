#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define oops(m, x)                                                             \
    {                                                                          \
        perror(m);                                                             \
        exit(x);                                                               \
    }
int main(int argc, char const *argv[]) {
    int p[2];
    int newfd, pid;
    if (argc != 3) {
        fprintf(stderr, "Usage: pipe cmd1 cmd2\n");
        exit(1);
    }
    if (pipe(p) == -1) {
        oops("Cannot get a pipe", 1);
    }
    if ((pid = fork()) == -1) {
        oops("Cannot fork", 2);
    }
    if (pid > 0) {
        close(p[1]);
        if (dup2(p[0], 0) == -1) {
            oops("could not redirect stdin", 3);
        }
        close(p[0]);
        execlp(argv[2], argv[2], NULL);
        oops(argv[2], 4);
    } else {
        close(p[0]);
        if (dup2(p[1], 1) == -1) {
            oops("could not redirect stdout", 3);
        }
        close(p[1]);
        execlp(argv[1], argv[1], NULL);
        oops(argv[1], 5);
    }

    return 0;
}
