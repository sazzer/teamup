#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

int main(void) {
    initscr();
    keypad(stdscr, TRUE);
    nonl();
    cbreak();
    echo();
    curs_set(0);
    refresh();

    start_color();

    int r = 0;
    int c = 0;
    for (int i = 0; i < std::min(COLOR_PAIRS, COLORS); ++i) {
        init_pair(i, i, COLOR_BLACK);
        attrset(0);
        attron(COLOR_PAIR(i));
        mvprintw(r, c, "%d", i % 10);
        ++c;
        if (i % 10 == 9) {
            c = 0;
            ++r;
        }
    }

    refresh();
    getch();
    endwin();
}

