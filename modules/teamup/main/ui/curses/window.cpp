#include "ui/curses/window.h"
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Window::Impl {
                WINDOW* window;
            };

            Window::Window(const WindowBounds& bounds) : pImpl(new Impl) {
                pImpl->window = newwin(bounds.height,
                        bounds.width,
                        bounds.y,
                        bounds.x);
            }

            Window::~Window() {
                delwin(pImpl->window);
            }
            void Window::render() const {
                wborder(pImpl->window, 0, 0, 0, 0, 0, 0, 0, 0);
                wnoutrefresh(pImpl->window);
            }
        }
    }
}
