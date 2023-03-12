#include <curses.h>
#include <stdio.h>
#include <unistd.h>

#define LEFTEDGE 0
#define RIGHTEDGE 100
#define ROW 10

int main(int argc, char const *argv[]) {
    char *message = "Hello";
    char *blank = "     ";
    int dir = +1;
    int pos = LEFTEDGE;
    initscr();
    clear();
    while (1) {
        move(ROW, pos);
        addstr(message);
        move(LINES - 1, COLS - 1);
        refresh();
        sleep(1);
        move(ROW, pos);
        addstr(blank);
        pos += dir;
        if (pos >= RIGHTEDGE) {
            dir = -1;
        }
        if (pos <= LEFTEDGE) {
            dir = +1;
        }
    }
    return 0;
}
