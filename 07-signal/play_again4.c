#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define QUESTION "Do you want another transaction."
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int get_response(char *, int);
void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
int get_ok_char();
void ctrl_c_handler(int);

int main(int argc, char const *argv[]) {
    int response;
    tty_mode(0);
    set_cr_noecho_mode();
    set_nodelay_mode();
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);
    response = get_response(QUESTION, TRIES);
    tty_mode(1);
    return response;
}

int get_response(char *question, int maxtries) {
    int input = -1;
    printf("%s(y/n)?", question);
    fflush(stdout);
    while (1) {
        sleep(SLEEPTIME);
        input = tolower(get_ok_char());
        if (input == (int)'y') {
            return 0;
        }
        if (input == (int)'n') {
            return 1;
        }
        if (maxtries-- == 0) {
            return 2;
        }
        BEEP;
    }
}

int get_ok_char() {
    int c;
    while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL)
        ;
    return c;
}

void set_cr_noecho_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodelay_mode() {
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
}

void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    if (how == 0) {
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    } else {
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }
}

void ctrl_c_handler(int signum) {
    tty_mode(1);
    exit(1);
}