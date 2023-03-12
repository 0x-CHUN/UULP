#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS 20
#define ARGLEN 100

int execute(char *args[]);
char *makestring(char *buf);

int main(int argc, char const *argv[]) {
    char *args[MAXARGS + 1];
    int numargs = 0;
    char argbuf[ARGLEN];

    while (numargs < MAXARGS) {
        printf("Arg[%d]?", numargs);
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') {
            args[numargs++] = makestring(argbuf);
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
    execvp(args[0], args);
    perror("execvp failed");
    exit(1);
}

char *makestring(char *buf) {
    buf[strlen(buf) - 1] = '\0';
    char *cp = (char *)malloc(sizeof(strlen(buf) + 1));
    if (cp == NULL) {
        fprintf(stderr, "No memory");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}
