#include <curses.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define MSG "hello"
#define BLK "     "

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done = 0;

void on_alarm(int signum);
void on_input(int signum);
void enable_kbd_signals();
int set_ticker(int n_msecs);

int main() {
    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO, on_input);
    enable_kbd_signals();
    signal(SIGALRM, on_alarm);
    set_ticker(delay);

    move(row, col);
    addstr(MSG);

    while (!done) {
        pause();
    }

    endwin();
    return 0;
}

void on_input(int signum) {
    int c = getch();
    if (c == 'Q' || c == EOF) {
        done = 1;
    } else if (c == ' ') {
        dir *= -1;
    }
}

void on_alarm(int signum) {
    signal(SIGALRM, on_alarm);
    mvaddstr(row, col, BLK);
    col += dir;
    mvaddstr(row, col, MSG);
    refresh();

    if (dir == -1 && col <= 0) {
        dir = 1;
    }
    if (dir == 1 && col + strlen(MSG) >= COLS) {
        dir = -1;
    }
}

void enable_kbd_signals() {
    fcntl(0, F_SETOWN, getpid());
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_ASYNC);
}

int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usecs;
    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}