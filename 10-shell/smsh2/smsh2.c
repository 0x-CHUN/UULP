#include "smsh.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFL_PROMPT "> "

void setup() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n) {
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}

int main(int argc, char const *argv[]) {
    char *cmdline, *prompt, **args;
    int result;
    prompt = DFL_PROMPT;
    setup();
    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((args = splitline(cmdline)) != NULL) {
            process(args);
            freelist(args);
        }
        free(cmdline);
    }

    return 0;
}
