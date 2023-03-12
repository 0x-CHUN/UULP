#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARGS 20
#define ARGLEN 100

char *make_string(char *buf);
int execute(char *args[]);

int main() {
    int numargs = 0;
    char buf[ARGLEN + 1];
    *buf = '\0';
    char *args[MAXARGS + 1];
    for (int i = 0; i < MAXARGS + 1; i++) {
        args[i] = NULL;
    }

    while (numargs < MAXARGS) {
        printf("arg[%d]", numargs);
        if (fgets(buf, ARGLEN, stdin) && *buf != '\n') {
            args[numargs++] = make_string(buf);
        } else {
            if (numargs > 0) {
                args[numargs] = NULL;
                execute(args);
                numargs = 0;
            }
        }
    }

    return 0;
}

int execute(char *args[]) {
    pid_t pid = fork();
    int child_status = 0;

    switch (pid) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        if (-1 == execvp(args[0], args)) {
            const char *p = NULL;
            for (int i = 0; i < MAXARGS + 1; i++) {
                p = args[i];
                if (p != NULL) {
                    fprintf(stderr, "debug: arg[%d]: %s\n", i, p);
                }
            }

            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
        break;
    default:
        while (wait(&child_status) != pid) {
        };
        printf("child exited with status: %d %d\n", child_status >> 8,
               child_status & 0xff);
    };
}

char *make_string(char *buf) {
    buf[strlen(buf) - 1] = '\0';

    char *cp = (char *)malloc(sizeof(strlen(buf) + 1));

    if (NULL == cp) {
        fprintf(stderr, "no memory available");
        exit(EXIT_FAILURE);
    }
    strncpy(cp, buf, strlen(buf) + 1);

    return cp;
}