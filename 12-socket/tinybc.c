#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define oops(m, x)                                                             \
    {                                                                          \
        perror(m);                                                             \
        exit(x);                                                               \
    }

void be_dc(int *, int *);
void be_bc(int *, int *);
void fatal(char *);

int main(int argc, char const *argv[]) {
    int pid, todc[2], fromdc[2];
    if (pipe(todc) == -1 || pipe(fromdc) == -1) {
        oops("pipe failed", 1);
    }
    if ((pid = fork()) == -1) {
        oops("cannot fork", 2);
    }
    if (pid == 0) {
        be_dc(todc, fromdc);
    } else {
        be_bc(todc, fromdc);
        wait(NULL);
    }
    return 0;
}

void be_dc(int to_dc[2], int from_dc[2]) {
    if (dup2(to_dc[0], 0) == -1) {
        oops("dc: cannot redirect stdin", 3);
    }
    close(to_dc[0]);
    close(to_dc[1]);

    if (dup2(from_dc[1], 1) == -1) {
        oops("dc: cannot redirect stdout", 4);
    }
    close(from_dc[0]);
    close(from_dc[1]);

    execlp("dc", "dc", "-", NULL);
    oops("cannot run dc", 5);
}

void be_bc(int to_dc[2], int from_dc[2]) {
    int num1 = 0;
    int num2 = 0;
    char operation[BUFSIZ] = {'\0'};
    char message[BUFSIZ] = {'\0'};
    FILE *fpout = NULL;
    FILE *fpin = NULL;

    close(to_dc[0]);
    close(from_dc[1]);

    fpout = fdopen(to_dc[1], "w");
    fpin = fdopen(from_dc[0], "r");
    if (fpout == NULL || fpin == NULL) {
        fatal("Error converting pipes to streams");
    }

    printf("tinybc: ");
    while (fgets(message, BUFSIZ, stdin) != NULL) {
        if (sscanf(message, "%d %s %d", &num1, operation, &num2) != 3) {
            printf("syntax error\n");
            continue;
        }
        if (fprintf(fpout, "%d\n%d\n%c\np\n", num1, num2, *operation) == EOF) {
            fatal("Error writing");
        }
        fflush(fpout);

        if (fgets(message, BUFSIZ, fpin) == NULL) {
            break;
        }
        printf("%d %c %d = %s", num1, *operation, num2, message);
        printf("tinybc: ");
    }
    fclose(fpout);
    fclose(fpin);
}

void fatal(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}