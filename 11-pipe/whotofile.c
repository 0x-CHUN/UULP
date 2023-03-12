#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int pid;
    int fd;
    printf("About to run who into a file!\n");
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        close(1);
        fd = creat("userlist", 0644);
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    }
    if (pid != 0) {
        wait(NULL);
        printf("Done running who. Result in userlist\n");
    }
    return 0;
}
