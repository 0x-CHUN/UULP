#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define QUESTION "Do you want another transaction."

int get_response(char *);
void tty_mode(int);
void set_cr_noecho_mode();

int main(int argc, char const *argv[]) {
    int response;
    tty_mode(0);
    set_cr_noecho_mode();
    response = get_response(QUESTION);
    tty_mode(1);
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

void set_cr_noecho_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
    static struct termios original_mode;
    if (how == 0) {
        tcgetattr(0, &original_mode);
    } else {
        tcsetattr(0, TCSANOW, &original_mode);
    }
}