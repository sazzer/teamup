#include "ui/ui.h"
#include <memory>
#include <easylogging++.h>
#include <ncurses.h>
#include <unistd.h>

namespace Teamup {
    namespace UI {
        class CursesUI {
            public:
                CursesUI() {
                    LOG(DEBUG) << "Starting Curses UI";
                    // Do all of the initial setup
                    initscr();
                    keypad(stdscr, TRUE);
                    nonl();
                    cbreak();
                    echo();
                    if (has_colors()) {
                        start_color();

                        init_pair(1, COLOR_RED,     COLOR_BLACK);
                        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
                        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
                        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
                        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
                        init_pair(6, COLOR_CYAN,    COLOR_BLACK);
                        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
                    }

                    clear();
                    attrset(COLOR_PAIR(5));
                    mvprintw(1, 1, "Hello, World!");
                    refresh();
                }
                ~CursesUI() {
                    LOG(DEBUG) << "Stopping Curses UI";
                    endwin();
                }
            private:
        };

        static std::unique_ptr<CursesUI> cursesUi;

        void start() {
            cursesUi.reset(new CursesUI);
            sleep(5);
        }
    }
}

