#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void wakeup(int signum) { printf("Alarm received from kernel\n"); }

int main(int argc, char const *argv[]) {
    signal(SIGALRM, wakeup);
    printf("About to sleep for 4 seconds\n");
    alarm(4);
    pause();
    printf("Morning so soon?\n");
    return 0;
}
