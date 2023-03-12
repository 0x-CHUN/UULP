#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction."

int get_response(char *);

int main(int argc, char const *argv[]) {
    int response;
    response = get_response(QUESTION);
    return response;
}

int get_response(char *question) {
    int input = -1;
    printf("%s(y/n)?", question);
    while (1) {
        switch (input = getchar()) {
        case 'Y':
        case 'y':
            return 0;
        case 'n':
        case 'N':
        case EOF:
            return 1;
        default:
            printf("\ncannot understand %c, ", input);
            printf("Please type y or n\n");
        }
    }
}
