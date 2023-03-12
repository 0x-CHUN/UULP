#include <curses.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    initscr();
    clear();
    for (int i = 0; i < LINES; i++) {
        move(i, i + i);
        if (i % 2 == 1) {
            standout();
        }
        addstr("Hello world");
        if (i % 2 == 1) {
            standend();
        }
    }
    refresh();
    getch();
    endwin();
}
