#ifndef TEAMUP_UI_CURSES_CURSES_H
#define TEAMUP_UI_CURSES_CURSES_H

#include "ui/curses/window_bounds.h"
#include "ui/curses/window_renderer.h"
#include <memory>

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * The actual Curses UI Implementation
             */
            class Curses {
            public:
                /**
                 * Construct the Curses wrapper
                 */
                Curses();
                /**
                 * Destroy the Curses wrapper
                 */
                ~Curses();
                /**
                 * Get the Width of the UI
                 * @return The width of the UI
                 */
                unsigned int width() const;
                /**
                 * Get the Height of the UI
                 * @return The height of the UI
                 */
                unsigned int height() const;

                /**
                 * Actually render the UI
                 */
                void render() const;
                /**
                 * Create a new window to render on the screen
                 * @param name   The internal name of the window
                 * @param bounds The bounds of the window
                 * @param renderer The renderer to use for the window
                 */
                void createWindow(const std::string& name, const WindowBounds& bounds, std::function<void(const WindowRenderer&)> renderer);
            protected:
            private:
                /** The internal implementation */
                struct Impl;
                /** The pImpl */
                std::unique_ptr<Impl> pImpl;
            };
        }
    }
}


#endif // TEAMUP_UI_CURSES_CURSES_H
