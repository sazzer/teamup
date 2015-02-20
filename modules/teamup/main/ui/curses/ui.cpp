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

                    WINDOW *logs, *status, *map;
                    int logsHeight = 10;
                    int statusWidth = 30;
                    logs = newwin(logsHeight, COLS, LINES - logsHeight, 0);
                    status = newwin(LINES - logsHeight, statusWidth, 0, COLS - statusWidth);
                    map = newwin(LINES - logsHeight, COLS - statusWidth, 0, 0);

                    box(logs, 0, 0);
                    box(status, 0, 0);

                    wrefresh(logs);
                    wrefresh(status);
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
            sleep(1);
        }
    }
}

