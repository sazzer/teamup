#include "ui/ui.h"
#include <memory>
#include <easylogging++.h>

namespace Teamup {
    namespace UI {
        class CursesUI {
            public:
                CursesUI() {
                    LOG(DEBUG) << "Starting Curses UI";
                }
                ~CursesUI() {
                    LOG(DEBUG) << "Stopping Curses UI";
                }
            private:
        };

        static std::unique_ptr<CursesUI> cursesUi;

        void start() {
            cursesUi.reset(new CursesUI);
        }
    }
}

