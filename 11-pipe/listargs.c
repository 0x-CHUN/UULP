#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Number of args:%d, Args are: \n", argc);
    for (int i = 0; i < argc; i++) {
        printf("args[%d] %s\n", i, argv[i]);
    }
    return 0;
}
