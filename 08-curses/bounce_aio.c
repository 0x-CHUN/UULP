#include <aio.h>
#include <curses.h>
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

struct aiocb kbcbuf;

void on_alarm(int signum);
void on_input(int signum);
int set_ticker(int n_msecs);
void setup_aio_buffer();

int main() {
    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO, on_input);

    setup_aio_buffer();
    aio_read(&kbcbuf);
    signal(SIGALRM, on_alarm);

    mvaddstr(row, col, MSG);
    refresh();
    set_ticker(delay);

    while (!done) {
        pause();
    }
    endwin();
    return 0;
}

void on_alarm(int signum) {
    signal(SIGALRM, on_alarm);
    mvaddstr(row, col, BLK);
    col += dir;
    mvaddstr(row, col, MSG);
    refresh();

    if (col <= 0 && dir == -1) {
        dir *= -1;
    }

    if (col + strlen(MSG) >= COLS && dir == 1) {
        dir *= -1;
    }
}

void on_input(int signum) {
    int c = -1;
    char *cp = (char *)kbcbuf.aio_buf;
    if (aio_error(&kbcbuf) != 0) {
        perror("reading failed");
    } else {
        if (aio_return(&kbcbuf) == 1) {
            c = *cp;
            if (c == 'Q' || c == EOF) {
                done = 1;
            } else if (c == ' ') {
                dir *= -1;
            }
        }
    }

    aio_read(&kbcbuf);
}

void setup_aio_buffer() {
    char buf[1] = {0};
    kbcbuf.aio_fildes = 0;
    kbcbuf.aio_buf = buf;
    kbcbuf.aio_nbytes = 1;
    kbcbuf.aio_offset = 0;

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo = SIGIO;
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