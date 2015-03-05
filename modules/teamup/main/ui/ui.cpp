#include "ui/ui.h"
#include <easylogging++.h>
#include <memory>
#include "ui/curses/curses.h"
#include "ui/curses/window_bounds.h"

namespace Teamup {
    namespace UI {
        static std::unique_ptr<Teamup::UI::Curses::Curses> cursesUi;

        void start() {
            LOG(TRACE) << "Starting UI";
            cursesUi.reset(new Teamup::UI::Curses::Curses);

            const unsigned int height = cursesUi->height();
            const unsigned int width = cursesUi->width();
            LOG(DEBUG) << "UI size is " << width << " x " << height;

            // For now we'll just hard-code some sizes.
            // TODO: Make these responsive
            const unsigned int logWindowHeight = 12;
            const unsigned int questWindowWidth = 22;
            const unsigned int charWindowWidth = 22;


            const Teamup::UI::Curses::WindowBounds mapWindowBounds {
                .x = charWindowWidth,
                .y = 0,
                .width = width - charWindowWidth - questWindowWidth,
                .height = height - logWindowHeight
            };
            const Teamup::UI::Curses::WindowBounds logWindowBounds {
                .x = 0,
                .y = mapWindowBounds.height,
                .width = width,
                .height = logWindowHeight
            };
            const Teamup::UI::Curses::WindowBounds questWindowBounds {
                .x = 0,
                .y = 0,
                .width = questWindowWidth,
                .height = mapWindowBounds.height
            };
            const Teamup::UI::Curses::WindowBounds charWindowBounds {
                .x = mapWindowBounds.x + mapWindowBounds.width,
                .y = 0,
                .width = charWindowWidth,
                .height = mapWindowBounds.height
            };

            LOG(DEBUG) << "Map Window Size: " << mapWindowBounds;
            LOG(DEBUG) << "Log Window Size: " << logWindowBounds;
            LOG(DEBUG) << "Quest Window Size: " << questWindowBounds;
            LOG(DEBUG) << "Character Window Size: " << charWindowBounds;

            cursesUi->createWindow("map", mapWindowBounds, [](auto bounds){});
            cursesUi->createWindow("log", logWindowBounds, [](auto bounds){});
            cursesUi->createWindow("quest", questWindowBounds, [](auto bounds){});
            cursesUi->createWindow("character", charWindowBounds, [](auto bounds){});

            cursesUi->render();
        }
    }
}
