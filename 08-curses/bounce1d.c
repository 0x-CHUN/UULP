#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define MESSAGE "hello"
#define BLANK "     "

int set_ticker(int);

int row = 10;
int col = 0;
int dir = 1;
int MESSAGE_LEN = strlen(MESSAGE);

void move_msg(int signum) {
    signal(SIGALRM, move_msg);

    move(row, col);
    addstr(BLANK);
    col += dir;
    move(row, col);
    addstr(MESSAGE);
    refresh();

    if (dir == -1 && col <= 0) {
        dir = 1;
    }

    if (dir == 1 && (col + MESSAGE_LEN) >= COLS) {
        dir = -1;
    }
}

int main(int argc, char const *argv[]) {
    int delay = 200;
    int ndelay;
    int c;
    initscr();
    crmode();
    noecho();
    clear();

    move(row, col);
    addstr(MESSAGE);
    signal(SIGALRM, move_msg);
    set_ticker(delay);

    while (1) {
        ndelay = 0;
        c = getch();
        if (c == 'Q' || c == 'q') {
            break;
        }
        if (c == ' ') {
            dir = -dir;
        }
        if (c == 'f' && delay > 2) {
            ndelay = delay / 2;
        }

        if (c == 's') {
            ndelay = delay * 2;
        }

        if (ndelay > 0) {
            delay = ndelay;
            set_ticker(delay);
        }
    }

    endwin();
    return 0;
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