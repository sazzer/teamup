#ifndef TEAMUP_UI_CURSES_WINDOW_H
#define TEAMUP_UI_CURSES_WINDOW_H

#include <memory>
#include "ui/window_bounds.h"
#include "ui/window_renderer.h"
#include <functional>

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
                 * @param bounds The bounds of the window
                 * @param renderer The functor to render the window contents
                 */
                Window(const WindowBounds& bounds, std::function<void(WindowRenderer&)> renderer);
                /**
                 * Destroy the window
                 */
                ~Window();
                /**
                 * Render this window to the UI
                 */
                void render();

                /**
                 * Get the bounds of the window
                 * @return the bounds
                 */
                const WindowBounds& bounds() const;
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
