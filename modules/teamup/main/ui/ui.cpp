#include "ui/ui.h"
#include <easylogging++.h>
#include <memory>
#include "ui/curses/curses.h"

namespace Teamup {
    namespace UI {
        static std::unique_ptr<Teamup::UI::Curses::Curses> cursesUi;

        void start() {
            LOG(TRACE) << "Starting UI";
            cursesUi.reset(new Teamup::UI::Curses::Curses);

            const unsigned int height = cursesUi->height();
            const unsigned int width = cursesUi->width();
            LOG(DEBUG) << "UI size is " << width << " x " << height;
        }
    }
}