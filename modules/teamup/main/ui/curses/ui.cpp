#include "ui/ui.h"
#include <memory>
#include <unistd.h>
#include "ui/curses/curses.h"

namespace Teamup {
    namespace UI {
        class CursesUI {
            public:
                CursesUI() {
                    Curses::setup();
                    unsigned int logsHeight = 10;
                    unsigned int statusWidth = 30;
                    unsigned int overallWidth = Curses::width();
                    unsigned int overallHeight = Curses::height();

                    Curses::createWindow("logs", 
                            0, 
                            overallHeight - logsHeight, 
                            overallWidth, 
                            logsHeight);
                    Curses::createWindow("status", 
                            overallWidth - statusWidth, 
                            0, 
                            statusWidth, 
                            overallHeight - logsHeight);

                    Curses::configureWindow("logs", [](auto& logs) {
                        logs.title("Log");
                        logs.bordered(true);
                        });
                    Curses::configureWindow("status", [](auto& status) {
                        status.title("Status");
                        status.bordered(true);
                        });

                    Curses::createWindow("map", 
                            0, 
                            0, 
                            overallWidth - statusWidth, 
                            overallHeight - logsHeight);

                    Curses::focusWindow("status");
                    Curses::render();
                }
                ~CursesUI() {
                    Curses::shutdown();
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

