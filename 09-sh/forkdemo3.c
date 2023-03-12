#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before: my pid is %d\n", getpid());

    pid_t pid = fork();

    if (-1 == pid) {
        perror("fork()");
    } else if (0 == pid) {
        printf("I am the child process. my pid = %d\n", getpid());
    } else {
        printf("I am the parent process. my pid = %d\n", getpid());
    }
    return 0;
}