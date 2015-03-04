#ifndef TEAMUP_UI_CURSES_WINDOW_H
#define TEAMUP_UI_CURSES_WINDOW_H

#include <memory>
#include "ui/curses/window_bounds.h"

namespace Teamup {
    namespace UI {
        namespace Curses {

            /**
             * Representation of a Window on the Curses screen
             */
            class Window {
            public:
                /**
                 * Construct the window
                 */
                Window(const WindowBounds& bounds);
                /**
                 * Destroy the window
                 */
                ~Window();
                /**
                 * Render this window to the UI
                 */
                void render() const;
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

#endif // TEAMUP_UI_CURSES_WINDOW_H
