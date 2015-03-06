#ifndef TEAMUP_UI_CURSES_WINDOW_RENDERER_H
#define TEAMUP_UI_CURSES_WINDOW_RENDERER_H

#include "ui/curses/window_bounds.h"

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * Interface to use to render elements into a window
             */
            class WindowRenderer {
            public:
                /**
                 * Get the bounds of the window to render into
                 * @return the bounds
                 */
                virtual const WindowBounds& bounds() const = 0;

                /**
                 * Render a simple string at the given location
                 * @param x The X-Ordinate to render the string at
                 * @param y The Y-Ordinate to render the string at
                 * @param str The string to render
                 */
                virtual void renderString(const unsigned int x, const unsigned int y, const std::string& str) = 0;
            };
        }
    }
}

#endif // TEAMUP_UI_CURSES_WINDOW_RENDERER_H
