#include "varlib.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int execute(char *argv[]) {
    int pid;
    int child_info = -1;
    if (argv[0] == NULL) {
        return 0;
    }
    if ((pid = fork()) == -1) {
        perror("Fork()");
    } else if (pid == 0) {
        environ = VLtable2environ() ;
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);
        perror("cannot execute command");
        exit(1);
    } else {
        if (wait(&child_info) == -1) {
            perror("wait");
        }
        return child_info;
    }
}