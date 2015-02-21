#include "ui/ui.h"
#include <memory>
#include <unistd.h>
#include "ui/curses/curses.h"

namespace Teamup {
    namespace UI {
        namespace Curses {
            class CursesUI {
                public:
                    CursesUI() : curses_(new Curses) {
                        unsigned int logsHeight = 10;
                        unsigned int statusWidth = 30;
                        unsigned int overallWidth = curses_->width();
                        unsigned int overallHeight = curses_->height();


                        curses_->createWindow("logs", 
                                0, 
                                overallHeight - logsHeight, 
                                overallWidth, 
                                logsHeight);
                        curses_->createWindow("status", 
                                overallWidth - statusWidth, 
                                0, 
                                statusWidth, 
                                overallHeight - logsHeight);

                        curses_->configureWindow("logs", [](auto& logs) {
                            logs.title("Log");
                            logs.bordered(true);
                            });
                        curses_->configureWindow("status", [](auto& status) {
                            status.title("Status");
                            status.bordered(true);
                            });

                        curses_->createWindow("map", 
                                0, 
                                0, 
                                overallWidth - statusWidth, 
                                overallHeight - logsHeight);

                        curses_->focusWindow("status");
                        curses_->render();
                    }
                private:
                    /** The wrapper around curses */
                    std::unique_ptr<Curses> curses_;
            };
        }

        static std::unique_ptr<Curses::CursesUI> cursesUi;

        void start() {
            cursesUi.reset(new Curses::CursesUI);
            sleep(5);
        }
    }
}

