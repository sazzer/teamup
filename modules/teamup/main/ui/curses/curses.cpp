#include "ui/curses/curses.h"
#include <easylogging++.h>
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            Curses::Curses() {
                LOG(TRACE) << "Starting Curses";
                initscr();
                keypad(stdscr, TRUE);
                nonl();
                cbreak();
                echo();
                curs_set(0);
                refresh();

                if (has_colors())
                {
                    start_color();

                    for (int i = 0; i < COLORS; ++i) {
                        init_pair(i, i, COLOR_BLACK);
                    }
                }
            }

            Curses::~Curses() {
                LOG(TRACE) << "Stopping Curses";
                getch();
                endwin();
            }

            unsigned int Curses::width() const {
                return COLS;
            }

            unsigned int Curses::height() const {
                return LINES;
            }
        }
    }
}