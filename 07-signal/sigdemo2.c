#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    signal(SIGINT, SIG_IGN);
    printf("Can't stop!\n");
    while (1) {
        sleep(1);
        printf("haha\n");
    }

    return 0;
}
