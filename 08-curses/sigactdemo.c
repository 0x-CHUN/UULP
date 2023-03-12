#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define INPUTLEN 100

void int_handler(int signum) {
    printf("Called with signal: %d\n", signum);
    sleep(signum);
    printf("done handling signal %d\n", signum);
}

int main(int argc, char const *argv[]) {
    struct sigaction new_handler;
    sigset_t blocked;
    char x[INPUTLEN];
    *x = '\0';

    new_handler.sa_handler = int_handler;
    new_handler.sa_flags = SA_RESETHAND;

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    new_handler.sa_mask = blocked;

    if (-1 == sigaction(SIGINT, &new_handler, NULL)) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    } else {
        while (1) {
            if (fgets(x, INPUTLEN, stdin) == NULL) {
                break;
            }
            printf("input: %s", x);
        }
    }
    return 0;
}
