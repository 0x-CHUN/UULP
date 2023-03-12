#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f(int signum) { printf("OUCH! \n"); }

int main(int argc, char const *argv[]) {
    void f(int);
    signal(SIGINT, f);
    for (int i = 0; i < 5; i++) {
        printf("Hello\n");
        sleep(1);
    }
    return 0;
}
