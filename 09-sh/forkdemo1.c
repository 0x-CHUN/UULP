#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t mypid = getpid();
    printf("Before: my pid is %d\n", mypid);
    pid_t ret_from_fork = fork();
    if (ret_from_fork == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("After: my pid is %d, fork() said %d\n", getpid(), ret_from_fork);
    return 0;
}
