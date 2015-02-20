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
                    initscr();
                    clear();
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

