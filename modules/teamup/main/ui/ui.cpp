#include "ui/ui.h"
#include <easylogging++.h>
#include <memory>
#include "ui/curses/curses.h"
#include "ui/window_bounds.h"
#include "ui/windows/log.h"

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


            const Teamup::UI::WindowBounds mapWindowBounds {
                .x = charWindowWidth,
                .y = 0,
                .width = width - charWindowWidth - questWindowWidth,
                .height = height - logWindowHeight
            };
            const Teamup::UI::WindowBounds logWindowBounds {
                .x = 0,
                .y = mapWindowBounds.height,
                .width = width,
                .height = logWindowHeight
            };
            const Teamup::UI::WindowBounds questWindowBounds {
                .x = 0,
                .y = 0,
                .width = questWindowWidth,
                .height = mapWindowBounds.height
            };
            const Teamup::UI::WindowBounds charWindowBounds {
                .x = mapWindowBounds.x + mapWindowBounds.width,
                .y = 0,
                .width = charWindowWidth,
                .height = mapWindowBounds.height
            };

            LOG(DEBUG) << "Map Window Size: " << mapWindowBounds;
            LOG(DEBUG) << "Log Window Size: " << logWindowBounds;
            LOG(DEBUG) << "Quest Window Size: " << questWindowBounds;
            LOG(DEBUG) << "Character Window Size: " << charWindowBounds;

            Teamup::UI::Windows::LogWindow logWindowController;

            cursesUi->createWindow("map", mapWindowBounds, [](auto& renderer){});
            cursesUi->createWindow("log", logWindowBounds, logWindowController);
            cursesUi->createWindow("quest", questWindowBounds, [](auto& renderer){});
            cursesUi->createWindow("character", charWindowBounds, [](auto& renderer){});

            cursesUi->render();
        }
    }
}
