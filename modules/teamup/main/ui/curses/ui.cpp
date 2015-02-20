#include "ui/ui.h"
#include "ui/curses/window.h"
#include <memory>
#include <easylogging++.h>
#include <ncurses.h>
#include <unistd.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
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

                        int logsHeight = 10;
                        int statusWidth = 30;
                        Window logs(0, LINES - logsHeight, COLS, logsHeight);
                        logs.title("Log");
                        logs.bordered(true);
                        Window status(COLS - statusWidth, 0, statusWidth, LINES - logsHeight);
                        status.title("Status");
                        status.bordered(true);
                        Window map(0, 0, COLS - statusWidth, LINES - logsHeight);

                        logs.render();
                        status.render();
                        map.render();
                        doupdate();
                    }
                    ~CursesUI() {
                        LOG(DEBUG) << "Stopping Curses UI";
                        endwin();
                    }
                private:
            };
        }

        static std::unique_ptr<Curses::CursesUI> cursesUi;

        void start() {
            cursesUi.reset(new Curses::CursesUI);
            sleep(5);
        }
    }
}

