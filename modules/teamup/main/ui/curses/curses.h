#ifndef TEAMUP_UI_CURSES_CURSES_H
#define TEAMUP_UI_CURSES_CURSES_H

#include <memory>
#include "ui/curses/window.h"

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * Enumeration of the colours supported
             */
            enum class Colours {
                BLACK,
                RED,
                GREEN,
                YELLOW,
                BLUE,
                MAGENTA,
                CYAN,
                WHITE
            };
            /**
             * Set up Curses ready to use
             */
            void setup();
            /**
             * Shut down Curses
             */
            void shutdown();
            /**
             * Get the width of the Curses UI
             * @return the width
             */
            unsigned int width();
            /**
             * Get the height of the Curses UI
             * @return the height
             */
            unsigned int height();
            /**
             * Render the UI
             */
            void render();
            /**
             * Create a new window to render into
             * @param name The internal name of the window
             * @param x The X-Ordinate
             * @param y The Y-Ordinate
             * @param width The width
             * @param height The height
             */
            void createWindow(const std::string& name, 
                    const unsigned int x,
                    const unsigned int y,
                    const unsigned int width,
                    const unsigned int height);
            /**
             * Configure the window with the given name
             * @param name The name of the window
             * @param callback The callback to configure the window with
             */
            void configureWindow(const std::string& name, 
                    std::function<void(Window&)> callback);
            /**
             * Mark the named Window as focused
             * @param name The name of the window
             */
            void focusWindow(const std::string& name);
            /**
             * Get the ID of the colour pair for the requested colour and shade
             * @param colour The colour to get
             * @param shade The shade of the colour to get
             * @return the colour ID
             */
            int getColour(Colours colour, int shade);
        }
    }
}

#endif
