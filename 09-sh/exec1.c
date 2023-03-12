#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    char *args[3];
    args[0] = "ls";
    args[1] = "-l";
    args[2] = 0;
    printf("*** About exec ls -l\n");
    execvp("ls", args);
    printf("*** ls is done!\n");
    return 0;
}
