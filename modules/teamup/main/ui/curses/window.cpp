#include "ui/curses/window.h"
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Window::Impl {
                WINDOW* window;
            };

            Window::Window() : pImpl(new Impl) {
                pImpl->window = newwin(10, // width
                        10, // height
                        0, // y
                        0);// x
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
